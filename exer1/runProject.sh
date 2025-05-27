# Archive: runProject.sh
# Uso: ./runProject.sh [args]  # Make run with args
#      ./runProject.sh         # Make run with default tests

# Test list
DEFAULT_TESTS=(
    "3,4,2 14"
    "5,2,1,8 16"
)

# Run the test with the provided arguments
run_program() {
    local args="$1"
    make run ARGS="$args"
}

# Run provided arguments
if [ $# -gt 0 ]; then
    run_program "$*"
    exit 0
fi

# Run all default tests
for test_args in "${DEFAULT_TESTS[@]}"; do
    run_program "$test_args"
done