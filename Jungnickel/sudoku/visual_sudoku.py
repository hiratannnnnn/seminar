import tkinter as tk
from tkinter import ttk
import re

class SudokuVisualizer:
    def __init__(self, filename, initial_file=None):
        self.window = tk.Tk()
        self.window.title("Sudoku Solver Visualizer")
        self.window.geometry("600x700")

        self.initial_board = [[0 for _ in range(9)] for _ in range(9)]
        self.board = [[0 for _ in range(9)] for _ in range(9)]
        self.steps = []
        self.current_step = 0

        if initial_file:
            self.load_initial_board(initial_file)

        self.load_steps(filename)
        self.create_gui()
        self.update_display()

    def load_initial_board(self, filename):
        try:
            with open(filename, 'r') as f:
                lines = f.readlines()

            for i, line in enumerate(lines[1:]):
                if i >= 9:
                    break
                values = line.strip().split()
                for j, val in enumerate(values):
                    if j >= 9:
                        break
                    self.initial_board[i][j] = int(val)
                    self.board[i][j] = int(val)

            print(f"Loaded initial board from {filename}")
        except FileNotFoundError:
            print(f"Initial file {filename} not found")

    def load_steps(self, filename):
        try:
            with open(filename, 'r') as f:
                content = f.read()

            place_pattern = r'\[DEBUG\] placing (\d+) to \((\d+), (\d+)\)'
            remove_pattern = r'<-- removing (\d+) from \((\d+), (\d+)\)'

            for line in content.split('\n'):
                place_match = re.search(place_pattern, line)
                remove_match = re.search(remove_pattern, line)

                if place_match:
                    num = int(place_match.group(1))
                    row = int(place_match.group(2))
                    col = int(place_match.group(3))
                    self.steps.append(('place', row, col, num))
                elif remove_match:
                    num = int(remove_match.group(1))
                    row = int(remove_match.group(2))
                    col = int(remove_match.group(3))
                    self.steps.append(('remove', row, col, num))

            print(f"Loaded {len(self.steps)} steps")
        except FileNotFoundError:
            print(f"File {filename} not found")

    def create_gui(self):
        main_frame = tk.Frame(self.window)
        main_frame.pack(padx=20, pady=20)

        info_frame = tk.Frame(main_frame)
        info_frame.pack(pady=10)

        self.step_label = tk.Label(info_frame, text="Step: 0 / 0", font=("Arial", 14))
        self.step_label.pack()

        self.action_label = tk.Label(info_frame, text="Action: -", font=("Arial", 12))
        self.action_label.pack()

        board_frame = tk.Frame(main_frame)
        board_frame.pack(pady=20)

        self.cells = []
        for i in range(9):
            row = []
            for j in range(9):
                cell_frame = tk.Frame(board_frame,
                                    bg='black' if (i//3 + j//3) % 2 == 0 else 'gray',
                                    width=50, height=50)
                cell_frame.grid(row=i, column=j, padx=1, pady=1)
                cell_frame.pack_propagate(False)

                cell_label = tk.Label(cell_frame, text="", font=("Arial", 16, "bold"),
                                    bg='white', fg='black', width=3, height=2)
                cell_label.pack(expand=True, fill='both')
                row.append(cell_label)
            self.cells.append(row)

        control_frame = tk.Frame(main_frame)
        control_frame.pack(pady=20)

        tk.Button(control_frame, text="← Previous", command=self.prev_step,
                 font=("Arial", 12), width=10).pack(side=tk.LEFT, padx=5)

        tk.Button(control_frame, text="Next →", command=self.next_step,
                 font=("Arial", 12), width=10).pack(side=tk.LEFT, padx=5)

        tk.Button(control_frame, text="Reset", command=self.reset,
                 font=("Arial", 12), width=10).pack(side=tk.LEFT, padx=5)

        speed_frame = tk.Frame(main_frame)
        speed_frame.pack(pady=10)

        tk.Label(speed_frame, text="Auto Speed:").pack(side=tk.LEFT)
        self.speed_var = tk.IntVar(value=500)
        speed_scale = tk.Scale(speed_frame, from_=100, to=2000, orient=tk.HORIZONTAL,
                              variable=self.speed_var, length=200)
        speed_scale.pack(side=tk.LEFT, padx=5)

        tk.Button(speed_frame, text="Auto Play", command=self.auto_play,
                 font=("Arial", 10)).pack(side=tk.LEFT, padx=5)

        tk.Button(speed_frame, text="Stop", command=self.stop_auto,
                 font=("Arial", 10)).pack(side=tk.LEFT, padx=5)

        self.window.bind('<Left>', lambda e: self.prev_step())
        self.window.bind('<Right>', lambda e: self.next_step())
        self.window.bind('<space>', lambda e: self.auto_play())
        self.window.focus_set()

        self.auto_playing = False

    def update_display(self):
        for i in range(9):
            for j in range(9):
                value = self.board[i][j]
                text = str(value) if value != 0 else ""

                if self.initial_board[i][j] != 0:
                    self.cells[i][j].config(text=text, bg='lightgray', fg='black',
                                          font=("Arial", 16, "bold"))
                else:
                    self.cells[i][j].config(text=text, bg='white', fg='blue',
                                          font=("Arial", 16, "normal"))

        if self.current_step > 0:
            action, row, col, num = self.steps[self.current_step - 1]
            if self.initial_board[row][col] == 0:
                self.cells[row][col].config(bg='lightblue' if action == 'place' else 'lightcoral')
            self.action_label.config(text=f"Last Action: {action.title()} {num} at ({row},{col})")
        else:
            self.action_label.config(text="Action: -")

        self.step_label.config(text=f"Step: {self.current_step} / {len(self.steps)}")

    def apply_step(self, step_index):
        if 0 <= step_index < len(self.steps):
            action, row, col, num = self.steps[step_index]
            if action == 'place':
                self.board[row][col] = num
            else:
                self.board[row][col] = 0

    def next_step(self):
        if self.current_step < len(self.steps):
            self.apply_step(self.current_step)
            self.current_step += 1
            self.update_display()

    def prev_step(self):
        if self.current_step > 0:
            self.current_step -= 1
            action, row, col, num = self.steps[self.current_step]
            if action == 'place':
                self.board[row][col] = 0
            else:
                self.board[row][col] = num
            self.update_display()

    def reset(self):
        for i in range(9):
            for j in range(9):
                self.board[i][j] = self.initial_board[i][j]
        self.current_step = 0
        self.stop_auto()
        self.update_display()

    def auto_play(self):
        if not self.auto_playing:
            self.auto_playing = True
            self.auto_step()

    def auto_step(self):
        if self.auto_playing and self.current_step < len(self.steps):
            self.next_step()
            self.window.after(self.speed_var.get(), self.auto_step)
        else:
            self.auto_playing = False

    def stop_auto(self):
        self.auto_playing = False

    def run(self):
        self.window.mainloop()

if __name__ == "__main__":
    visualizer = SudokuVisualizer("seq.txt", "prob.txt")
    visualizer.run()
