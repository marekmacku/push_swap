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

void get_chunk_range(int chunk_index, int chunk_count, int total_size, int *min, int *max)
{
    int chunk_size;
    
    chunk_size = total_size / chunk_count;
    *min = chunk_index * chunk_size;
    
    if (chunk_index == chunk_count - 1)
        *max = total_size - 1;
    else
        *max = *min + chunk_size - 1;
}

/* Find position of a value in stack (distance from top) */
int	get_position_in_stack(t_stack *stack, int target_value)
{
    int distance;
    t_node *current;
    if (!stack || !stack->top)
        return  (-1);
    distance = 0;
    current = stack->top;
    while(current)
    {
        if (current->value == target_value)
            return (distance);
        distance++;
        current = current->next;
    }
    return (-1);
}

/* Main function to sort large stacks using chunk-based algorithm */
void	sort_large(t_stack *stack_a, t_stack *stack_b, int size)
{
    int chunk_count;
    
    if (!stack_a || !stack_a->top)
        return ;
    
    chunk_count = calculate_chunk_count(size);
    push_chunks_to_b(stack_a, stack_b, chunk_count, size);
    push_back_to_a_optimized(stack_a, stack_b);
}

/* Phase 1: Push chunks to stack B sequentially */
void	push_chunks_to_b(t_stack *stack_a, t_stack *stack_b, int chunk_count, int total_size)
{
    int	chunk_idx;
    int	min_val;
    int	max_val;
    int	target;
    int	chunk_target_size;
    int	pushed;

    if (!stack_a || !stack_a->top)
        return ;
    chunk_idx = chunk_count - 1;  // START FROM HIGHEST CHUNK (largest values first)
    while (chunk_idx >= 0 && stack_a->size > 0)
    {
        get_chunk_range(chunk_idx, chunk_count, total_size, &min_val, &max_val);
        chunk_target_size = total_size / chunk_count;
        if (chunk_idx == chunk_count - 1)
            chunk_target_size += total_size % chunk_count;
        pushed = 0;
        while (pushed < chunk_target_size && stack_a->size > 0)
        {
            target = find_largest_cheapest_in_chunk(stack_a, min_val, max_val);
            if (target == -1)
                break ;
            rotate_to_top(stack_a, target, 1);
            pb(stack_a, stack_b);
            pushed++;
        }
        chunk_idx--;
    }
}

/* Rotate stack to bring target value to top using cheapest direction */
void	rotate_to_top(t_stack *stack, int target_value, int is_stack_a)
{
    int	pos;
    int	ra_cost;
    int	rra_cost;

    if (!stack || !stack->top)
        return ;
    pos = get_position_in_stack(stack, target_value);
    if (pos == -1 || pos == 0)
        return ;
    ra_cost = pos;
    rra_cost = stack->size - pos;
    if (ra_cost <= rra_cost)
    {
        while (ra_cost > 0)
        {
            ra_cost--;
            if (is_stack_a == 1)
                ra(stack);
            else
                rb(stack);
        }
    }
    else
    {
        while (rra_cost > 0)
        {
            rra_cost--;
            if (is_stack_a == 1)
                rra(stack);
            else
                rrb(stack);
        }
    }
}

// --------- --------- --------- OPTIMIZED WAY  --------- --------- ---------

void execute_move(t_stack *a, t_stack *b, t_move *move)
{
    int common_rotations;
    
    if (move->a_dir == move->b_dir && move->a_dir != 0)
    {
        common_rotations = (move->a_cost < move->b_cost)
            ? move->a_cost : move->b_cost;
        do_common_rotations(a, b, common_rotations, move->a_dir);
        move->a_cost -= common_rotations;
        move->b_cost -= common_rotations;
    }
    do_a_rotations(a, move->a_cost, move->a_dir);
    do_b_rotations(b, move->b_cost, move->b_dir);
}

void push_back_to_a_optimized(t_stack *a, t_stack *b)
{
    t_move move;
    
    while (b->top)
    {
        find_cheapest_move(a, b, &move);
        execute_move(a, b, &move);
        pa(a, b);
    }
}

