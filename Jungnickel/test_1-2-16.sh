#!/bin/bash
# filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/test_1-2-16.sh

# 結果を保存するディレクトリを作成
RESULTS_DIR="./results_1-2-16"
mkdir -p $RESULTS_DIR

# 結果ファイルの定義
RESULTS_FILE="$RESULTS_DIR/test_1-2-16_results.txt"
echo "プルーファーコードテスト結果" > $RESULTS_FILE
echo "実行日時: $(date)" >> $RESULTS_FILE
echo "====================================" >> $RESULTS_FILE
echo "入力 -> 出力（頂点の次数）" >> $RESULTS_FILE
echo "------------------------------------" >> $RESULTS_FILE

# 現在のディレクトリに移動
cd "$(dirname "$0")"

# コンパイル
echo "コンパイル中..."
gcc -o test_1-2-16 1-2-16.c -DSIMPLE_OUTPUT

if [ $? -ne 0 ]; then
    echo "コンパイルに失敗しました。"
    exit 1
fi

# テストケース実行関数
run_test() {
    local test_num=$1
    local test_case="${*:2}"
    
    echo -e "\nテストケース$test_num: $test_case"
    
    # 結果を一時ファイルに保存
    local temp_result=$(./test_1-2-16 $test_case)
    
    # 結果から次数のみを抽出
    local degrees=$(echo "$temp_result" | grep -E "頂点.*:" | awk '{print $3}' | tr '\n' ' ')
    
    # 結果ファイルに追加（入力 -> 出力）
    echo "[$test_case] -> [$degrees]" >> $RESULTS_FILE
}

# テストケース実行
echo "テストケース実行中..."
run_test 1 4 4 4 5
run_test 2 1 2 3 4
run_test 3 2 2 2
run_test 4 3 3 5 5
run_test 5 1 1 1 1 1

# クリーンアップ
rm -f test_1-2-16

echo -e "\nすべてのテスト完了"
echo "テスト結果は $RESULTS_FILE に保存されました"