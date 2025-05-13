#!/bin/bash
# filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/test_1-2-17-2.sh

RESULTS_DIR="./results_1-2-17-2"
mkdir -p $RESULTS_DIR

RESULTS_FILE="$RESULTS_DIR/test_1-2-17-2_results.txt"
echo "Graph generation test results" > $RESULTS_FILE
echo "Date: $(date)" >> $RESULTS_FILE
echo "====================================" >> $RESULTS_FILE
echo "Input (Degrees) -> Edges Generated" >> $RESULTS_FILE
echo "------------------------------------" >> $RESULTS_FILE

cd "$(dirname "$0")"

echo "Compiling..."
gcc -o test_1-2-17-2 1-2-17-2.c

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

run_test() {
    local test_num=$1
    local test_case="${*:2}"
    local temp_file="$RESULTS_DIR/temp_output_$test_num.txt"

    echo -e "\nTest case $test_num: $test_case"
    
    # プログラムの出力を一時ファイルに保存
    ./test_1-2-17-2 $test_case > "$temp_file" 2>&1
    
    # Edge 情報を抽出 (Edge の行を完全に表示)
    local edges=$(grep "Edge" "$temp_file" | sed 's/^/  /')
    
    # 結果をファイルに保存
    echo -e "Test case $test_num: [$test_case]" >> $RESULTS_FILE
    echo -e "Generated edges:" >> $RESULTS_FILE
    echo "$edges" >> $RESULTS_FILE
    echo -e "-------------------------------------\n" >> $RESULTS_FILE
    
    # 詳細結果も保存
    echo -e "\n----- Test case $test_num details -----" >> "$RESULTS_DIR/full_results.txt"
    cat "$temp_file" >> "$RESULTS_DIR/full_results.txt"
    echo -e "-------------------------------------\n" >> "$RESULTS_DIR/full_results.txt"
    
    # 一時ファイルを削除
    rm "$temp_file"
}

echo "Running test cases..."

# スター型のグラフ (一つの高次数頂点と残りは次数1の頂点)
run_test 1 1 1 1 1 4         # n=5, sum=8
run_test 2 1 1 1 1 1 5       # n=6, sum=10
run_test 3 1 1 1 1 1 1 6     # n=7, sum=12

# パス型のグラフ (多くが次数2の頂点)
run_test 4 1 2 2 2 1         # n=5, sum=8
run_test 5 1 2 2 2 2 1       # n=6, sum=10
run_test 6 1 2 2 2 2 2 1     # n=7, sum=12

# バランスのとれたグラフ
run_test 7 1 1 3 3            # n=4, sum=6
run_test 8 1 1 1 3 2 2       # n=6, sum=10
run_test 9 1 1 1 3 2 2 2     # n=7, sum=12

# 複数の分岐点を持つグラフ
run_test 10 2 2 2 1 1         # n=5, sum=8
run_test 11 2 2 2 2 1 1       # n=6, sum=10
run_test 12 3 3 1 1 1 1       # n=6, sum=10

rm -f test_1-2-17-2

echo -e "\nAll tests completed"
echo "Results saved to:"
echo "- $RESULTS_FILE (summary)"
echo "- $RESULTS_DIR/full_results.txt (detailed output)"