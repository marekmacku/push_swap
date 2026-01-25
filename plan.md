# Push_swap Implementation Plan

## Overview

This project requires implementing a sorting algorithm using two stacks (a and b) with limited operations. The goal is to minimize operations to meet strict benchmarks: <700 operations for 100 numbers and <5500 operations for 500 numbers.

## Algorithm Strategy

### Best Algorithms for This Problem

1. **Hardcoded Solutions (3-5 elements)**

- For 3 elements: Use a lookup table or decision tree (max 2-3 operations)
- For 5 elements: Use a lookup table or decision tree (max 12 operations)
- These are optimal and should be handled separately

2. **Chunk-Based Algorithm (100+ elements)** - RECOMMENDED

- Divide the stack into chunks (e.g., 5-7 chunks for 100 numbers, 8-12 chunks for 500 numbers)
- Push elements to stack b based on which chunk they belong to
- Maintain some order in stack b (e.g., keep larger numbers at top)
- Push back to stack a in sorted order
- **Expected performance**: ~500-650 operations for 100 numbers, ~4500-5200 for 500 numbers

3. **Turk Algorithm** (Advanced variant)

- Similar to chunk-based but with cost calculation
- For each element, calculate the cost to move it to the correct position
- Choose the element with minimum cost
- More complex but can achieve lower operation counts

4. **Hybrid Approach** (Best for 100% validation)

- Small stacks (≤5): Hardcoded optimal solutions
- Medium stacks (6-100): Chunk-based with optimized chunk size
- Large stacks (101-500): Chunk-based with dynamic chunk sizing

## Implementation Structure

### Core Components

1. **Stack Data Structure**

- Implement a stack using a linked list or array
- Support operations: push, pop, swap, rotate, reverse_rotate
- Track stack size and top element

2. **Input Parsing & Validation**

- Parse command-line arguments into integers
- Validate: integers only, no duplicates, within INT limits
- Handle error cases (display "Error\n" on stderr)

3. **Operations Implementation**

- Implement all 11 operations: sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
- Operations should modify the stacks and can optionally print the operation name

4. **Sorting Logic**

- **Small stacks (≤5)**: Hardcoded decision trees or lookup tables
- **Large stacks**: Chunk-based algorithm with these steps:

a. Calculate optimal chunk size based on stack sizeb. Assign each number to a chunk based on its valuec. Push chunks to stack b (maintain order - larger numbers at top)d. Push back to stack a in sorted order (find minimum, rotate to top, push)

5. **Optimization Techniques**

- Combine operations (e.g., use rr/rrr when both stacks need rotation)
- Calculate costs before making moves
- Avoid unnecessary operations
- Use reverse operations when they're cheaper

## File Structure

```javascript
push_swap/
├── Makefile
├── push_swap.h (header file)
├── main.c (entry point, argument parsing)
├── stack.c / stack.h (stack data structure and operations)
├── operations.c (sa, sb, pa, pb, ra, rb, rra, rrb, ss, rr, rrr)
├── validation.c (input validation, duplicate checking)
├── sort_small.c (hardcoded solutions for 3-5 elements)
├── sort_large.c (chunk-based algorithm)
└── utils.c (helper functions: find_min, find_max, get_position, etc.)
```



## Key Algorithm Details

### Chunk-Based Algorithm Steps:

1. **Chunk Calculation**

- For N elements, use approximately sqrt(N) to N/10 chunks
- Example: 100 numbers → 5-7 chunks, 500 numbers → 8-12 chunks

2. **Pushing to Stack B**

- Iterate through stack a
- For each element, determine its target chunk
- Push to stack b, maintaining order (larger numbers stay at top)
- Use rotations to position elements optimally

3. **Pushing Back to Stack A**

- Find the maximum element in stack b
- Rotate stack b to bring it to top
- Push to stack a
- Repeat until stack b is empty
- Finally, rotate stack a to put minimum at top

### Optimization Tips:

- **Cost Calculation**: Before each move, calculate the cost (number of rotations needed) for each possible action
- **Operation Combination**: Use rr/rrr/ss when both stacks need the same operation
- **Smart Rotations**: Choose ra or rra based on which requires fewer operations
- **Chunk Size Tuning**: Experiment with different chunk sizes to find optimal performance

## Testing Strategy

1. Test with 3, 4, 5 elements (should be optimal)
2. Test with 100 random numbers (must be <700 operations)
3. Test with 500 random numbers (must be <5500 operations)
4. Test edge cases: already sorted, reverse sorted, duplicates (should error)



### New Checklist
Implementation checklist
- [ ] Pre-processing: Normalize values to ranks 0..N-1
- [ ] Chunk calculation: Use N/11 for 100, N/15-20 for 500
- [ ] Phase 1: Process chunks sequentially, one at a time
- [ ] Intra-chunk sorting: Push to B in descending order
- [ ] Rotation optimization: Always use cheapest direction (ra vs rra)
- [ ] Operation combination: Use rr/rrr when possible
- [ ] Phase 2: Push maximums from sorted-descending chunks
- [ ] LIS detection: Preserve sorted prefixes
- [ ] Hardcoded cases: n≤5 use optimal solutions
- [ ] Testing: Validate with 1000 random inputs
This corrected algorithm guarantees benchmark compliance and is simpler than radix-based approaches.
