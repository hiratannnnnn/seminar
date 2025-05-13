#!/bin/bash

RESULTS_DIR="./results_1-2-16"
mkdir -p $RESULTS_DIR

RESULTS_FILE="$RESULTS_DIR/test_1-2-16_results.txt"
echo "Prufer code test results" > $RESULTS_FILE
echo "Date: $(date)" >> $RESULTS_FILE
echo "====================================" >> $RESULTS_FILE
echo "Input -> Output (vertex degrees)" >> $RESULTS_FILE
echo "------------------------------------" >> $RESULTS_FILE

cd "$(dirname "$0")"

echo "Compiling..."
gcc -o test_1-2-16 1-2-16.c -DSIMPLE_OUTPUT

if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

run_test() {
    local test_num=$1
    shift
    local test_case=("$@")

    echo -e "\nTest case $test_num: ${test_case[*]}"

    local temp_result=$(./test_1-2-16 "${test_case[@]}")

    # Output is a single line of degrees
    local degrees=$(echo "$temp_result" | head -n 1)

    echo "[${test_case[*]}] -> [$degrees]" >> $RESULTS_FILE
}

echo "Running test cases..."
run_test 1 4 4 4 5
run_test 2 1 2 3 4
run_test 3 2 2 2
run_test 4 3 3 5 5
run_test 5 1 1 1 1 1
run_test 6 5 5 5 4 3 6 6 2 1 8

rm -f test_1-2-16

echo -e "\nAll tests completed"
echo "Results saved to $RESULTS_FILE"
