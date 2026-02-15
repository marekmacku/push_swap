#!/bin/bash

# Push_swap tester
# Tests correctness and counts operations for sizes: 2, 3, 4, 5, 50, 100, 300, 500
# The parser pushes each arg to the TOP of the stack, so the initial stack
# (top to bottom) is the REVERSE of the argument order.

PUSH_SWAP="./push_swap"
SIZES=(2 3 4 5 50 100 300 500)
RUNS_PER_SIZE=10
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m'

# 42 grading thresholds
THRESH_3=3
THRESH_5=12
THRESH_100=700
THRESH_500=5500

get_threshold() {
    case "$1" in
        3) echo $THRESH_3 ;;
        5) echo $THRESH_5 ;;
        100) echo $THRESH_100 ;;
        500) echo $THRESH_500 ;;
        *) echo "" ;;
    esac
}

# Generate N unique random numbers
generate_numbers() {
    python3 -c "
import random
nums = random.sample(range(-5000, 5001), $1)
print(' '.join(map(str, nums)))
"
}

# Python-based checker (handles all sizes correctly)
# The stack is built by pushing args one by one to the top,
# so initial stack_a (top-to-bottom) = reversed(args)
check_with_python() {
    local args="$1"
    local ops="$2"
    python3 << 'PYEOF'
import sys

def check(args_str, ops_str):
    nums = [int(x) for x in args_str.split()]
    # first argument = top of stack (standard push_swap convention)
    a = list(nums)
    b = []
    if ops_str.strip() == "":
        ops = []
    else:
        ops = [o.strip() for o in ops_str.strip().split('\n') if o.strip()]
    for op in ops:
        if op == 'sa':
            if len(a) >= 2: a[0], a[1] = a[1], a[0]
        elif op == 'sb':
            if len(b) >= 2: b[0], b[1] = b[1], b[0]
        elif op == 'ss':
            if len(a) >= 2: a[0], a[1] = a[1], a[0]
            if len(b) >= 2: b[0], b[1] = b[1], b[0]
        elif op == 'pa':
            if b: a.insert(0, b.pop(0))
        elif op == 'pb':
            if a: b.insert(0, a.pop(0))
        elif op == 'ra':
            if len(a) >= 2: a.append(a.pop(0))
        elif op == 'rb':
            if len(b) >= 2: b.append(b.pop(0))
        elif op == 'rr':
            if len(a) >= 2: a.append(a.pop(0))
            if len(b) >= 2: b.append(b.pop(0))
        elif op == 'rra':
            if len(a) >= 2: a.insert(0, a.pop())
        elif op == 'rrb':
            if len(b) >= 2: b.insert(0, b.pop())
        elif op == 'rrr':
            if len(a) >= 2: a.insert(0, a.pop())
            if len(b) >= 2: b.insert(0, b.pop())
        else:
            print('INVALID_OP: ' + op)
            return
    if len(b) != 0:
        print('KO')
    elif a == sorted(a):
        print('OK')
    else:
        print('KO')

import os
args_str = os.environ.get('PS_ARGS', '')
ops_str = os.environ.get('PS_OPS', '')
check(args_str, ops_str)
PYEOF
}

echo -e "${BOLD}========================================${NC}"
echo -e "${BOLD}       PUSH_SWAP TESTER${NC}"
echo -e "${BOLD}========================================${NC}"
echo -e "Runs per size: ${CYAN}${RUNS_PER_SIZE}${NC}"
echo ""

total_pass=0
total_fail=0

for size in "${SIZES[@]}"; do
    echo -e "${BOLD}--- Size: ${CYAN}${size}${BOLD} ---${NC}"
    pass=0
    fail=0
    min_ops=999999
    max_ops=0
    total_ops=0

    for ((run = 1; run <= RUNS_PER_SIZE; run++)); do
        ARG=$(generate_numbers "$size")

        # Run push_swap
        output=$(eval "$PUSH_SWAP $ARG" 2>/dev/null)
        exit_code=$?

        if [ $exit_code -ne 0 ]; then
            echo -e "  Run ${run}: ${RED}CRASH (exit code $exit_code)${NC}"
            ((fail++))
            continue
        fi

        # Count operations
        if [ -z "$output" ]; then
            num_ops=0
        else
            num_ops=$(echo "$output" | wc -l | tr -d ' ')
        fi

        # Verify with python checker (pass via env vars to avoid quoting issues)
        result=$(PS_ARGS="$ARG" PS_OPS="$output" check_with_python)

        if [ "$result" = "OK" ]; then
            ((pass++))
        else
            echo -e "  Run ${run}: ${RED}FAIL${NC} - $result (${num_ops} ops)"
            ((fail++))
            continue
        fi

        # Track operation counts
        total_ops=$((total_ops + num_ops))
        if [ "$num_ops" -lt "$min_ops" ]; then
            min_ops=$num_ops
        fi
        if [ "$num_ops" -gt "$max_ops" ]; then
            max_ops=$num_ops
        fi
    done

    # Results summary
    if [ "$pass" -gt 0 ]; then
        avg_ops=$((total_ops / pass))
    else
        avg_ops=0
    fi

    if [ "$fail" -eq 0 ]; then
        echo -e "  Result: ${GREEN}${pass}/${RUNS_PER_SIZE} OK${NC}"
    else
        echo -e "  Result: ${RED}${pass}/${RUNS_PER_SIZE} OK, ${fail} FAILED${NC}"
    fi

    if [ "$pass" -gt 0 ]; then
        echo -e "  Ops: min=${CYAN}${min_ops}${NC}  avg=${CYAN}${avg_ops}${NC}  max=${CYAN}${max_ops}${NC}"

        threshold=$(get_threshold "$size")
        if [ -n "$threshold" ]; then
            if [ "$max_ops" -le "$threshold" ]; then
                echo -e "  42 grade: ${GREEN}PASS${NC} (max ${max_ops} <= ${threshold})"
            else
                echo -e "  42 grade: ${YELLOW}OVER LIMIT${NC} (max ${max_ops} > ${threshold})"
            fi
        fi
    fi

    total_pass=$((total_pass + pass))
    total_fail=$((total_fail + fail))
    echo ""
done

echo -e "${BOLD}========================================${NC}"
echo -e "${BOLD}TOTAL: ${GREEN}${total_pass} passed${NC}, ${RED}${total_fail} failed${NC}"
echo -e "${BOLD}========================================${NC}"

if [ "$total_fail" -eq 0 ]; then
    exit 0
else
    exit 1
fi
