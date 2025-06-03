import tkinter as tk
import sys

class ChessBoard(tk.Canvas):
    def __init__(self, master, rows, cols, path=None, cell_size=60, *args, **kwargs):
        width = cols * cell_size
        height = rows * cell_size
        super().__init__(master, width=width, height=height, *args, **kwargs)
        self.rows = rows
        self.cols = cols
        self.cell_size = cell_size
        self.selected = None
        self.lines = {}  # {(cell1, cell2): line_id}
        self.path = path if path else []
        self.draw_board()
        self.bind("<Button-1>", self.on_click)
        if self.path:
            self.draw_path_edges(self.path)

    def draw_board(self):
        for r in range(self.rows):
            for c in range(self.cols):
                x1 = c * self.cell_size
                y1 = (self.rows - r - 1) * self.cell_size
                x2 = x1 + self.cell_size
                y2 = y1 + self.cell_size
                self.create_rectangle(x1, y1, x2, y2, fill="white", outline="black")
                idx = r * self.cols + c
                self.create_text(x1 + self.cell_size/2, y1 + self.cell_size/2, text=str(idx), font=("Arial", 14))

    def get_cell(self, event):
        c = event.x // self.cell_size
        r = self.rows - 1 - (event.y // self.cell_size)
        if 0 <= r < self.rows and 0 <= c < self.cols:
            return (r, c)
        return None

    def cell_center(self, r, c):
        x = c * self.cell_size + self.cell_size/2
        y = (self.rows - r - 1) * self.cell_size + self.cell_size/2
        return (x, y)

    def id_to_cell(self, idx):
        r = idx // self.cols
        c = idx % self.cols
        return (r, c)

    def draw_path_edges(self, path):
        for i in range(len(path) - 1):
            cell1 = self.id_to_cell(path[i])
            cell2 = self.id_to_cell(path[i+1])
            key = tuple(sorted([cell1, cell2]))
            if key not in self.lines:
                x1, y1 = self.cell_center(*cell1)
                x2, y2 = self.cell_center(*cell2)
                line_id = self.create_line(x1, y1, x2, y2, fill="blue", width=3)
                self.lines[key] = line_id

    def draw_path_step(self, from_id, to_id):
        cell1 = self.id_to_cell(from_id)
        cell2 = self.id_to_cell(to_id)
        key = tuple(sorted([cell1, cell2]))
        if key not in self.lines:
            x1, y1 = self.cell_center(*cell1)
            x2, y2 = self.cell_center(*cell2)
            line_id = self.create_line(x1, y1, x2, y2, fill="blue", width=3)
            self.lines[key] = line_id

    def on_click(self, event):
        cell = self.get_cell(event)
        if cell is None:
            return
        if self.selected is None:
            self.selected = cell
            x, y = self.cell_center(*cell)
            self.highlight = self.create_oval(x-8, y-8, x+8, y+8, outline="red", width=2)
        else:
            cell1 = self.selected
            cell2 = cell
            key = tuple(sorted([cell1, cell2]))
            id1 = cell1[0] * self.cols + cell1[1]
            id2 = cell2[0] * self.cols + cell2[1]
            if key in self.lines:
                self.delete(self.lines[key])
                del self.lines[key]
                # パスからも削除
                if (id1, id2) in zip(self.path, self.path[1:]):
                    idx = self.path.index(id1)
                    if idx+1 < len(self.path) and self.path[idx+1] == id2:
                        self.path.pop(idx+1)
                elif (id2, id1) in zip(self.path, self.path[1:]):
                    idx = self.path.index(id2)
                    if idx+1 < len(self.path) and self.path[idx+1] == id1:
                        self.path.pop(idx+1)
            else:
                x1, y1 = self.cell_center(*cell1)
                x2, y2 = self.cell_center(*cell2)
                line_id = self.create_line(x1, y1, x2, y2, fill="blue", width=3)
                self.lines[key] = line_id
                # パスに追加
                if not self.path:
                    self.path.append(id1)
                if self.path[-1] == id1:
                    self.path.append(id2)
                elif self.path[-1] == id2:
                    self.path.append(id1)
            self.delete(self.highlight)
            self.selected = None
            print("Hamiltonian path (vertex IDs):", self.path)

def load_path_from_file(filename):
    with open(filename, "r") as f:
        line = f.readline()
        return [int(x) for x in line.strip().split()]

def main():
    if len(sys.argv) >= 3:
        cols = int(sys.argv[1])
        rows = int(sys.argv[2])
        path = []
        if len(sys.argv) >= 4:
            path = load_path_from_file(sys.argv[3])
    else:
        cols, rows = 8, 6
        path = []
    root = tk.Tk()
    root.title("Chessboard Visualizer")
    board = ChessBoard(root, rows=rows, cols=cols, path=path)
    board.pack()
    root.mainloop()

if __name__ == "__main__":
    main()
