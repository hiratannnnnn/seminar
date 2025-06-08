compile

makeコマンドを利用する場合

```bash
make
```

Makefileを利用しない場合は、以下のコマンドを入力してください。

```bash
gcc -Iinclude -o report2 main_2.c ./srcs/*.c
gcc -Iinclude -o report5 main_5.c ./srcs/*.c

```

これで実行ファイル./report2, ./report5が作成されるはずです。

あとは、2番に対しては

```bash
./report2
```

```bash
./report5
```


作成者：平田智也
