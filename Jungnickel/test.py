import subprocess
import numpy as np
import matplotlib.pyplot as plt
import time

N = 100  # 試行回数
n = 50# 頂点数（必要に応じて変更）

edge_counts = []

for i in range(N):
    # Cプログラムを呼び出してグラフを生成
    subprocess.run(["./jung.exe", str(n)])
    # 数ミリ秒スリープ（例：20ミリ秒）
    time.sleep(0.1)
    # euler_graph.txtを読み込んで辺の本数をカウント
    with open("euler_graph.txt") as f:
        lines = f.readlines()
        matrix = [list(map(int, line.split())) for line in lines[1:]]
        edge_count = sum(sum(row) for row in matrix) // 2
        edge_counts.append(edge_count)

# 統計情報の表示
print(f"平均: {np.mean(edge_counts):.2f}")
print(f"標準偏差: {np.std(edge_counts):.2f}")
print(f"最小: {np.min(edge_counts)}, 最大: {np.max(edge_counts)}")

# ヒストグラムで可視化
plt.hist(edge_counts, bins=20, edgecolor='black')
plt.xlabel("Number of edges")
plt.ylabel("Frequency")
plt.title(f"Distribution of edge counts in random Euler graphs (n={n})")
plt.show()
