#include "push_swap.h"

int calculate_chunk_count(int size)
{
    if (size <= 16)
        return 1;
    else if (size <= 100)
        return 5;  // ~20 per chunk
    else if (size <= 500)
        return 11; // ~45 per chunk
    else
        return size / 50;
}

void get_chunk_range(t_chunk *chunk, int *min, int *max)
{
    int chunk_size;
    
    chunk_size = chunk->total_size / chunk->count;
    *min = chunk->index * chunk_size;
    if (chunk->index == chunk->count - 1)
        *max = chunk->total_size - 1;
    else
        *max = *min + chunk_size - 1;
}

static int	calculate_target_size(int chunk_index, int chunk_count, int total_size)
{
	int	size;

	size = total_size / chunk_count;
	if (chunk_index == chunk_count - 1)
		size += total_size % chunk_count;
	return (size);
}

static void	push_chunk_elements(t_stack *stack_a, t_stack *stack_b, t_chunk_range *range)
{
	int	target;
	int	pushed;

	pushed = 0;
	while (pushed < range->target_size && stack_a->size > 0)
	{
		target = find_largest_cheapest_in_chunk(stack_a, range->min, range->max);
		if (target == -1)
			break ;
		rotate_to_top(stack_a, target, 1);
		pb(stack_a, stack_b);
		pushed++;
	}
}

/* Phase 1: Push chunks to stack B sequentially */
void	push_chunks_to_b(t_stack *stack_a, t_stack *stack_b, int chunk_count, int total_size)
{
	int				chunk_idx;
	t_chunk			chunk;
	t_chunk_range	range;

	if (!stack_a || !stack_a->top)
		return ;
	chunk_idx = chunk_count - 1;
	chunk.count = chunk_count;
	chunk.total_size = total_size;
	while (chunk_idx >= 0 && stack_a->size > 0)
	{
		chunk.index = chunk_idx;
		get_chunk_range(&chunk, &range.min, &range.max);
		range.target_size = calculate_target_size(chunk_idx, chunk_count, total_size);
		push_chunk_elements(stack_a, stack_b, &range);
		chunk_idx--;
	}
}