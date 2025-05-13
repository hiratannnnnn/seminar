#!/bin/bash
# filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/test_jung.sh

RESULT_DIR="result_$(date +%Y%m%d_%H%M%S)"
mkdir -p $RESULT_DIR
RESULT_FILE="$RESULT_DIR/test_results.txt"

echo "=== Graph Generation and Prufer Code Test Results ===" > $RESULT_FILE
echo "Execution Date: $(date)" >> $RESULT_FILE
echo "========================================" >> $RESULT_FILE

run_test() {
    local test_num=$1
    local test_name=$2
    local degrees=("${@:3}")
    
    echo -e "\n=== Test ${test_num}: ${test_name} ===" | tee -a $RESULT_FILE
    
    echo -n "Degree Sequence: " | tee -a $RESULT_FILE
    for d in "${degrees[@]}"; do
        echo -n "$d " | tee -a $RESULT_FILE
    done
    echo "" | tee -a $RESULT_FILE
    
    echo -e "\nExecution Results:" | tee -a $RESULT_FILE
    echo "----------------------------------------" | tee -a $RESULT_FILE
    
    ./jung degrees "${degrees[@]}" | tee -a $RESULT_FILE
    
    echo "----------------------------------------" | tee -a $RESULT_FILE
}

run_prufer_test() {
    local test_num=$1
    local test_name=$2
    local prufer=("${@:3}")
    
    echo -e "\n=== Test ${test_num}: ${test_name} ===" | tee -a $RESULT_FILE
    
    echo -n "Prufer Code: " | tee -a $RESULT_FILE
    for p in "${prufer[@]}"; do
        echo -n "$p " | tee -a $RESULT_FILE
    done
    echo "" | tee -a $RESULT_FILE
    
    echo -e "\nExecution Results:" | tee -a $RESULT_FILE
    echo "----------------------------------------" | tee -a $RESULT_FILE
    
    ./jung prufer "${prufer[@]}" | tee -a $RESULT_FILE
    
    echo "----------------------------------------" | tee -a $RESULT_FILE
}

echo "Starting tests - Results will be saved to ${RESULT_FILE}"

echo -e "\n=== Graph Generation Tests ===" | tee -a $RESULT_FILE

run_test 1 "Star Graph" 1 1 1 1 4
run_test 2 "Path Graph" 1 2 2 2 1
run_test 3 "Balanced Graph" 1 1 3 3

echo -e "\n=== Prufer Code Tests ===" | tee -a $RESULT_FILE

run_prufer_test 4 "Prufer Code Example 1" 3 3 3 3 3 3 3 3 3 3
run_prufer_test 5 "Prufer Code Example 2" 1 2 3 4

echo -e "\nTest results are saved in ${RESULT_FILE}"