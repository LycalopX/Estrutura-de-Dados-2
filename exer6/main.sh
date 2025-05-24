#!/bin/bash
set -e

rm -rf build
mkdir build
cd build
cmake ..
cmake --build .

# If no arguments, run two predefined test cases
if [ $# -eq 0 ]; then
    echo "Running default test case: Pesos 8 1 5 com quicksort"
    ./main quicksort 8 1 5

    echo "Running default test case: Pesos 3 9 2 4 com heapsort"
    ./main heapsort 3 9 2 4
else
    ./main "$@"
fi