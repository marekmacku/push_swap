# Push Swap Algorithm Analysis

## Current Algorithm Flow

### Phase 1: Normalization
- Values are normalized to 0..(n-1) using quicksort
- Example: `[5, 2, 8, 1, 9, 3, 7, 4, 6]` → `[4, 1, 7, 0, 8, 2, 6, 3, 5]`

### Phase 2: Push Chunks to Stack B
1. Calculate chunk count (for size 9: 1 chunk)
2. Process chunks from highest to lowest (chunk_idx = chunk_count-1 down to 0)
3. For each chunk:
   - Find elements in chunk range [min, max]
   - Push cheapest-to-move elements to stack B
   - Result: Stack B contains elements, Stack A is empty

### Phase 3: Push Back to Stack A (THE PROBLEM AREA)
For each element in stack B:
1. `find_cheapest_move()` - finds cheapest element in B to move
2. For each element in B, calls `find_target_position()` to find where to insert in A
3. `execute_move()` - rotates both stacks to prepare for insertion
4. `pa()` - pushes element from B to A

## Critical Problems Identified

### Problem 1: `find_best_insert_pos()` Assumes Sorted Stack
**Location:** `update_move_utils.c:21-43`

```c
static int find_best_insert_pos(t_stack *stack_a, int value)
{
    // Finds smallest value > value
    // ASSUMES stack_a is sorted!
    if (current->value > value && current->value < best_val)
```

**Issue:** This function assumes stack A is sorted, but during insertion:
- Stack A starts empty
- First element: no problem (empty stack)
- Second element: might work if first was smallest
- **But as we insert more elements, if ANY insertion is wrong, the stack becomes unsorted**
- Then `find_best_insert_pos()` finds wrong position because it assumes sorted order

**Example:**
- Stack A: `[0, 2]` (sorted, missing 1)
- Insert value 1
- `find_best_insert_pos(1)` looks for smallest value > 1 → finds 2 at position 1
- Rotates to position 1, inserts → `[0, 1, 2]` ✓ CORRECT

But if stack is `[2, 0]` (unsorted):
- `find_best_insert_pos(1)` finds 2 at position 0
- Rotates to position 0 (no rotation needed)
- Inserts → `[1, 2, 0]` ✗ WRONG! Should be `[0, 1, 2]`

### Problem 2: Edge Case in `find_target_position()` for Large Values
**Location:** `update_move_utils.c:46-74`

When `target_pos == -1` (value > all in A):
```c
if (target_pos == -1) {
    // Find min position
    if (min_pos == 0)
        return (0);  // Don't rotate
    return (min_pos);  // Rotate min to top
}
```

**Issue:** Logic is inconsistent:
- If min is at position 0: return 0 → no rotation → insert at top
  - Result: `[new_value, min, ...]` which is `[min, ..., max, new_value]` in circular order ✓
- If min is at position > 0: return min_pos → rotate min to top → insert
  - Result: `[new_value, min, ...]` which should be correct ✓

**BUT:** This only works if stack A is sorted! If stack A is unsorted, finding min/max doesn't help.

### Problem 3: No Guarantee of Sorted Order Maintenance
**Location:** `move_utils.c:77-96`

The algorithm doesn't verify that each insertion maintains sorted order:
- After each `pa()`, stack A should be sorted (circularly)
- But if `find_target_position()` returns wrong position, order breaks
- Once order breaks, all subsequent insertions are wrong

### Problem 4: Circular Sorted Stack Logic
**Location:** Throughout insertion logic

The algorithm treats stack as circular sorted, meaning:
- `[0, 1, 2, 3, 4]` is sorted
- `[2, 3, 4, 0, 1]` is also sorted (circularly)
- `is_sorted()` only checks linear order from top

**Issue:** When inserting, we need to maintain circular sorted order, but:
- `find_best_insert_pos()` only works for linear sorted stacks
- If stack is `[2, 3, 4, 0, 1]` (circularly sorted), inserting 5 should go after 4
- But `find_best_insert_pos(5)` might not find the right position

## Root Cause Analysis

### The Core Issue:
**`find_best_insert_pos()` assumes the stack is linearly sorted from top to bottom, but:**
1. During insertion, stack might be circularly sorted (min not at top)
2. If any insertion goes wrong, stack becomes unsorted
3. Once unsorted, `find_best_insert_pos()` gives wrong answers
4. Wrong answers cause more wrong insertions
5. Cascade failure

### Why Some Tests Pass:
- Small stacks (size ≤ 5): Use different algorithm (`sort_for_three`, etc.)
- Stacks that happen to stay sorted during insertion
- Stacks where min stays at position 0 throughout

### Why Test Case `5 2 8 1 9 3 7 4 6` Fails:
1. After normalization: `[4, 1, 7, 0, 8, 2, 6, 3, 5]`
2. All elements pushed to B (size 9 → 1 chunk)
3. When pushing back:
   - First few insertions might work
   - At some point, stack A becomes unsorted (circularly or linearly)
   - `find_best_insert_pos()` starts giving wrong positions
   - Cascade failure

## Recommended Fixes

### Fix 1: Make `find_best_insert_pos()` Handle Circular Sorted Stacks
Instead of assuming linear sort, check all positions and find the correct insertion point even if stack is circularly sorted.

### Fix 2: Verify Sorted Order After Each Insertion
After each `pa()`, verify stack A is still sorted (circularly). If not, fix it before next insertion.

### Fix 3: Use Different Strategy for Large Values
When inserting value > all in A:
- Find maximum, not minimum
- Insert after maximum (which is before minimum in circular order)
- Ensure rotation logic handles this correctly

### Fix 4: Maintain Sorted Order Invariant
Ensure that after each insertion, the stack remains sorted. This might require:
- Re-checking the insertion position
- Potentially rotating the stack after insertion to maintain min-at-top (if needed)

## Current State Summary

✅ **Working:**
- Normalization
- Chunking and pushing to B
- Small stack sorting (≤5 elements)
- Cost calculation and move optimization

❌ **Broken:**
- Insertion logic when stack A is not linearly sorted
- Handling of circular sorted stacks during insertion
- Edge cases when inserting values larger than all in A
- Maintaining sorted order invariant during insertion

🔧 **Needs Fix:**
- `find_best_insert_pos()` to handle circular/unsorted stacks
- `find_target_position()` edge case handling
- Verification of sorted order after each insertion
- Better handling of the "value > all" case

