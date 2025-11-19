コンパイルするには、以下を実行してください。

### tests/ex_**.txt の作成

```bash
gcc ./srcs/*.c ./lib/*.c -I./include main_make_ex.c -o make_ex
```

### tests/ex_**.txt を読み、実行する

```bash
gcc ./srcs/*.c ./lib/*.c -I./include main.c -o solve
```

├─include
├─lib
├─srcs
└─tests

├─include
	ヘッダファイル
├─lib
	ライブラリ（基本的な操作をする関数）
├─srcs
	ソースファイル
└─tests
	テスト用テキストファイル（容量注意）

処理を変える場合
./srcs/main.c
を編集してください。
