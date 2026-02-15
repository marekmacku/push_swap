# Push_swap: Turk Algorithm Implementation Plan

## Context

The current push_swap uses a chunk-based sorting algorithm that pushes elements to stack B in chunk ranges (highest-first), then uses greedy cost-based insertion to push them back to A. This approach has two critical problems:

1. **Phase 1 (A-to-B) is suboptimal**: Chunks are pushed without considering B's state at all. The "largest cheapest in chunk" heuristic doesn't maintain any ordering in B, leading to expensive Phase 2 insertions.
2. **Missing final rotation**: After Phase 2, stack A is circularly sorted but the code never rotates the minimum to the top. The error prints on lines 78-81 of `sorts.c` confirm this awareness but the fix is absent.

The **Turk algorithm** is the proven solution for these benchmarks. It replaces Phase 1 with a cost-optimized push that maintains B in descending order, keeps the existing Phase 2 (which already works correctly), and adds the missing final rotation. Typical results: **550-650 ops for 100 numbers, 4800-5300 for 500**.

---

## What Changes

### Files to MODIFY (4 files):

| File | Change |
|------|--------|
| `push_swap.h` | Remove chunk structs/declarations, add new function declarations |
| `chunking.c` | **Full rewrite** -> Turk Phase 1 core (find_target_in_b, push_all_to_b) |
| `find_best_in_chunk.c` | **Full rewrite** -> Phase 1 cost calculator (find_cheapest_push_to_b) |
| `sorts.c` | Modify `sort_large()`, add `final_rotation()` |

### Files UNCHANGED (16 files):

All operation files, parsing files, `main.c`, `main_utils.c`, `normalize.c`, `quick_sort.c`, `sort_utils.c`, `sort_utils_2.c`, `find_cheapest_move.c`, `move_utils.c`, `update_move_utils.c`, `common_rotations.c`, `Makefile`.

---

## Phase 1: Update `push_swap.h`

**Remove** `t_chunk` and `t_chunk_range` structs.

**Remove** declarations: `calculate_chunk_count`, `get_chunk_range`, `push_chunks_to_b`, `find_largest_cheapest_in_chunk`.

**Add** declarations:
```c
int     find_max(t_stack *stack);
int     find_target_in_b(t_stack *stack_b, int value);
void    find_cheapest_push_to_b(t_stack *a, t_stack *b, t_move *move);
void    push_all_to_b(t_stack *stack_a, t_stack *stack_b);
void    final_rotation(t_stack *stack_a);
```

---

## Phase 2: Rewrite `chunking.c` — Turk Phase 1 Core

Delete all current content. New file has 5 functions (norminette max):

### `find_max(t_stack *stack)` — public
Linear scan for maximum value. Mirrors existing `find_min()`.

### `find_best_spot_in_b(t_stack *b, int value)` — static
Scans B for the **largest value that is strictly less than `value`**. Returns its position. Returns -1 if none found. This is the mirror of `find_best_insert_pos()` in update_move_utils.c (which finds smallest value > target for Phase 2).

### `find_target_in_b(t_stack *stack_b, int value)` — public
Calls `find_best_spot_in_b()`. If result is -1 (value is smaller than everything in B), falls back to position of max in B. This maintains B in circularly-descending order.

**Why this works**: When we `pb`, the value lands on TOP of B. If we rotate B so the "target" (largest value < ours) is on top, then after pb our new value sits above it — correct descending order. If our value is the new minimum, we place it above the maximum (circular wrap).

### `push_initial_two(t_stack *a, t_stack *b)` — static
Simply calls `pb` twice. With 0-1 elements in B, no cost calculation is meaningful.

### `push_all_to_b(t_stack *stack_a, t_stack *stack_b)` — public
Main Phase 1 loop:
1. Guard: return if `stack_a->size <= 3`
2. Call `push_initial_two()`
3. While `stack_a->size > 3`: call `find_cheapest_push_to_b()` to find optimal element, call `execute_move()` to rotate both stacks, call `pb()` to push

---

## Phase 3: Rewrite `find_best_in_chunk.c` — Phase 1 Cost Calculator

Delete all current content. New file has 3 functions:

### `set_move_data(t_move *move, t_element_info *elem, t_rotation_data *rot, int target_pos)` — static
Sets all fields of `t_move` from the computed rotation data. Keeps `a_cost/a_dir` for stack A rotations and `b_cost/b_dir` for stack B rotations, consistent with how `execute_move()` reads them.

### `check_and_update_push(t_move_context *ctx, t_element_info *elem)` — static
For one element in A: calls `find_target_in_b()` to get target position in B, calls `calc_dir_cost()` twice (once for A position, once for B target), calls `total_rotation_costs()` for combined cost, updates move if cheapest. Mirrors `check_and_update_move()` from `find_cheapest_move.c`.

### `find_cheapest_push_to_b(t_stack *a, t_stack *b, t_move *move)` — public
Iterates all elements in A, calls `check_and_update_push()` for each. After loop, `move` contains the optimal push. Mirrors `find_cheapest_move()` from `find_cheapest_move.c`.

**Key reuse**: `calc_dir_cost()`, `total_rotation_costs()`, `execute_move()` — all existing infrastructure works identically for both push directions. The `t_move` struct fields `a_cost/a_dir` always control stack A rotation and `b_cost/b_dir` always control stack B rotation.

---

## Phase 4: Modify `sorts.c`

### Modify `sort_large()`:
```
sort_large(stack_a, stack_b, size):
    push_all_to_b(stack_a, stack_b)   // Turk Phase 1
    sort_for_three(stack_a)            // Sort remaining 3
    push_back_to_a(stack_a, stack_b)   // Phase 2 (existing, unchanged)
    final_rotation(stack_a)            // Phase 3 (NEW)
```

### Add `final_rotation(t_stack *stack_a)`:
1. Early exit if already sorted
2. Find min value with `find_min()`
3. Rotate min to top with `rotate_to_top()` (already picks cheapest direction)

File total: 5 functions (sort_for_three, sort_for_four, sort_for_five, sort_large, final_rotation). Norminette OK.

---

## Norminette Compliance

| File | Functions | Max line count | Params max |
|------|-----------|----------------|------------|
| `chunking.c` | 5 (2 static, 3 public) | ~21 lines | 2 params |
| `find_best_in_chunk.c` | 3 (2 static, 1 public) | ~23 lines | 4 params |
| `sorts.c` | 5 (0 static, 5 public) | ~13 lines | 3 params |
| `push_swap.h` | N/A | N/A | N/A |

All functions under 25 lines. All files at or under 5 functions. All functions have max 4 parameters.

---

## Verification

```bash
# Build
make re

# 100-number benchmark (run multiple times, all must be < 700):
ARG=$(python3 -c "import random; l=list(range(1,101)); random.shuffle(l); print(' '.join(map(str,l)))"); ./push_swap $ARG | wc -l

# 500-number benchmark (run multiple times, all must be < 5500):
ARG=$(python3 -c "import random; l=list(range(1,501)); random.shuffle(l); print(' '.join(map(str,l)))"); ./push_swap $ARG | wc -l

# Edge cases:
./push_swap 1          # 0 operations
./push_swap 2 1        # 1 operation (sa)
./push_swap 1 2 3      # 0 operations (already sorted)
./push_swap 42         # 0 operations
```
