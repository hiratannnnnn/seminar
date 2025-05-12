#!/bin/bash
# filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/test_1-2-17.sh

RESULTS_DIR="./results_1-2-17"
mkdir -p $RESULTS_DIR

RESULTS_FILE="$RESULTS_DIR/test_1-2-17_results.txt"
echo "Prufer code test results" > $RESULTS_FILE
echo "Date: $(date)" >> $RESULTS_FILE
echo "====================================" >> $RESULTS_FILE
echo "Input -> Output (Prufer code)" >> $RESULTS_FILE
echo "------------------------------------" >> $RESULTS_FILE

cd "$(dirname "$0")"

echo "Compiling..."
gcc -o test_1-2-17 1-2-17.c -DSIMPLE_OUTPUT

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

run_test() {
    local test_num=$1
    local test_case="${*:2}"

    echo -e "\nTest case $test_num: $test_case"

    local temp_result=$(./test_1-2-17 $test_case)

    # Extract Prufer code
    local prufer=$(echo "$temp_result" | grep "Prufer code:" | cut -d':' -f2- | tr -d '\n')

    echo "[$test_case] -> [$prufer]" >> $RESULTS_FILE
}

echo "Running test cases..."
run_test 1 1 1 2 2 2         # n=5, sum=8
run_test 2 1 1 1 1 4         # n=5, sum=8
run_test 3 2 2 2 1 1         # n=5, sum=8
run_test 4 1 1 1 2 2 3       # n=6, sum=10
run_test 5 1 1 1 1 2 4       # n=6, sum=10
run_test 6 2 2 2 2 1 1       # n=6, sum=10
run_test 7 1 1 1 1 2 2 4     # n=7, sum=12
run_test 8 1 1 1 2 2 2 3     # n=7, sum=12
run_test 9 2 2 2 2 2 1 1     # n=7, sum=12
run_test 10 1 1 1 1 2 2 2 4  # n=8, sum=14
run_test 11 1 1 1 1 1 2 3 4  # n=8, sum=14
run_test 12 2 2 2 2 2 2 1 1  # n=8, sum=14

rm -f test_1-2-17

echo -e "\nAll tests completed"
echo "Results saved to $RESULTS_FILE"
