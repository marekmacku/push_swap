*This project has been created as part of the 42 curriculum by mmacku*

## Description

`push_swap` is a 42 school project that challenges you to sort a stack of integers using the fewest number of operations possible, with only two stacks and a limited set of instructions.

**Goal:** Given a list of integers on stack A, produce the shortest sequence of operations that leaves stack A sorted in ascending order, with stack B empty.

**Available operations:**

| Operation | Description |
|-----------|-------------|
| `sa` / `sb` | Swap the top two elements of stack A / B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` / `pb` | Push the top element of B to A / A to B |
| `ra` / `rb` | Rotate stack A / B upward (top goes to bottom) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` / `rrb` | Reverse rotate stack A / B (bottom goes to top) |
| `rrr` | `rra` and `rrb` simultaneously |

**Algorithm overview:**

The program uses different strategies depending on input size:

- **2 elements:** Single swap if needed.
- **3 elements:** Hardcoded decision tree covering all 6 permutations.
- **4–5 elements:** The minimum(s) are pushed to B, the remaining three are sorted, then elements are pushed back in order.
- **Large inputs (n > 5):** A greedy cost-based algorithm. All elements except three are pushed to stack B, with each push position chosen to minimize total rotation cost. The remaining three are sorted on A, then each element of B is pulled back to A at the cheapest possible position, and a final rotation aligns the minimum to the top.

Input is normalized to contiguous indices before sorting large stacks, which simplifies position calculations.

---

## Instructions

### Requirements

- A C compiler (`cc`) with support for C99 or later
- `make`

### Compilation

```bash
make
```

This produces the `push_swap` binary. Additional targets:

```bash
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Full recompile from scratch
```

### Execution

Pass integers as separate arguments or as a single quoted string:

```bash
./push_swap 3 1 4 1 5 9 2 6
./push_swap "3 1 4 1 5 9 2 6"
```

The program prints the list of operations to standard output, one per line. If the input is already sorted, no output is produced. On invalid input (non-integers, duplicates, out-of-range values), `Error` is written to standard error and the program exits with status `1`.

### Testing

A test script is included:

```bash
bash test_push_swap.sh
```

To check for memory leaks:

```bash
bash test_leaks.sh
```

You can also pipe the output into a checker (if available from 42's project resources):

```bash
ARG="3 1 4 1 5 9 2 6"
./push_swap $ARG | ./checker $ARG
```

---

## Resources

### References

- **push_swap — The least amount of moves with two stacks** — Lil Bear Hug (Medium)
  A popular walkthrough of algorithmic approaches used in this project.

- **Sorting Algorithms — Wikipedia**
  https://en.wikipedia.org/wiki/Sorting_algorithm
  Background on sorting complexity and comparison-based sorting lower bounds.

- **42 push_swap project subject (PDF)**
  The official project specification, available through the 42 intranet.

- **Visualizer by o-reo**
  https://github.com/o-reo/push_swap_visualizer
  A graphical tool to visualize the operations produced by your program.

### Use of AI

Claude (Anthropic) was used during this project for:

- **Writing this README** — structuring and drafting documentation.
- **Algorithm optimization** — evaluating trade-offs in the greedy cost-based approach, refining the rotation cost calculation, and identifying edge cases in the push-back phase.
- **Planning and performance analysis** — helping design the overall algorithm strategy, analyzing worst-case and average-case operation counts, and comparing chunking strategies.
