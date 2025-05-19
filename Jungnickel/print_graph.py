import matplotlib.pyplot as plt
import numpy as np
import sys

def read_adj_matrix(filename):
	with open(filename, 'r') as f:
		n = int(f.readline())
		matrix = []
		for _ in range(n):
			row = list(map(int, f.readline().split()))
			matrix.append(row)
	return n, matrix

def read_path(filename):
	with open(filename, 'r') as f:
		return list(map(int, f.read().split()))

def plot_graph_circle(n, matrix, path=None, step=None):
	plt.clf()
	angles = np.linspace(0, 2 * np.pi, n, endpoint=False)
	xs = np.cos(angles)
	ys = np.sin(angles)

	# 通常の辺
	for i in range(n):
		for j in range(i+1, n):
			if matrix[i][j]:
				plt.plot([xs[i], xs[j]],
						 [ys[i], ys[j]],
						 'k-', lw=1, zorder=1)
	# パスを強調（矢印で方向を表現）
	if path and step is not None and step > 0:
		ax = plt.gca()
		for a, b in zip(path, path[1:step+1]):
			ax.annotate(
				'',
				xy=(xs[b], ys[b]), xytext=(xs[a], ys[a]),
				arrowprops=dict(
					arrowstyle="-|>", color='red', lw=2,
					shrinkA=15, shrinkB=15, mutation_scale=20
				),
				zorder=2
			)
	plt.scatter(xs, ys, s=300, c='w', edgecolors='k', zorder=3)
	for i, (x, y) in enumerate(zip(xs, ys)):
		plt.text(x, y, str(i), ha='center', va='center',
				 fontsize=12, zorder=4)
	plt.axis('off')
	plt.axis('equal')
	plt.draw()

if __name__ == "__main__":
	if len(sys.argv) < 2:
		print("Usage: python print_graph.py <adj_matrix_file> [euler_path_file]")
		sys.exit(1)

	n, matrix = read_adj_matrix(sys.argv[1])
	path = None
	if len(sys.argv) > 2:
		path = read_path(sys.argv[2])

	plt.figure(figsize=(6, 6))

	if path:
		current_step = 1  # 最初は1本だけ表示

		def on_key(event):
			global current_step
			if event.key == 'right':
				if current_step < len(path) - 1:
					current_step += 1
					plot_graph_circle(n, matrix, path, step=current_step)
			elif event.key == 'left':
				if current_step > 1:
					current_step -= 1
					plot_graph_circle(n, matrix, path, step=current_step)

		plot_graph_circle(n, matrix, path, step=current_step)
		plt.gcf().canvas.mpl_connect('key_press_event', on_key)
		print("→キーで次の矢印、←キーで前の矢印を表示します。")
	else:
		plot_graph_circle(n, matrix)

	plt.show()
