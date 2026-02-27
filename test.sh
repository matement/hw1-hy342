#!/bin/bash

echo "Compiling..."
make
echo "====================================="
echo "      Running N-Queens Tests         "
echo "====================================="

# 1. Test the valid inputs from expected.txt
while read -r n expected; do
        if [ -z "$n" ]; then continue; fi

        start_time=$(date +%s%3N)

        output=$(./src/hw1 "$n" 2>/dev/null)

        # Record end time in ms
        end_time=$(date +%s%3N)

        # Calculate difference
        elapsed=$((end_time - start_time))

        result=$(echo "$output" | grep -o '[0-9]\+' | tail -n 1)

        if [ "$result" == "$expected" ]; then
                echo -e "N=$n \t \e[32m[ PASS ]\e[0m (Found: $result in ${elapsed}ms)"
        else
                echo -e "N=$n \t \e[31m[ FAIL ]\e[0m (Expected: $expected, but got: $result)"
        fi

done < expected.txt

echo "====================================="
echo "      Running Negative Tests         "
echo "====================================="
# 2. Test Invalid Input (N=16)
bad_n=16
expected_err="Error: Board size must be between 1 and 15"

start_time=$(date +%s%3N)
error_output=$(./src/hw1 "$bad_n" 2>&1)
end_time=$(date +%s%3N)

elapsed=$((end_time - start_time))

if echo "$error_output" | grep -q "$expected_err"; then
    echo -e "N=$bad_n \t \e[32m[ PASS ]\e[0m (Correctly rejected in ${elapsed}ms)"
else
    echo -e "N=$bad_n \t \e[31m[ FAIL ]\e[0m (Got: $error_output)"
fi
echo "====================================="
echo "             Done!                   "
echo "====================================="