#include "push_swap.h"

int find_largest_cheapest_in_chunk(t_stack *stack, int min_val, int max_val)
{
    t_node *curr;
    int     best_cost;
    int     best_val;
    int     pos;
    int     cost;

    if (!stack || !stack->top)
        return (-1);
    best_cost = stack->size + 1;
    best_val = -1;
    curr = stack->top;
    pos = 0;
    while (curr)
    {
        if (curr->value >= min_val && curr->value <= max_val)
        {
            cost = pos;
            if (pos > stack->size - pos)
                cost = stack->size - pos;
            if (cost < best_cost || (cost == best_cost && curr->value > best_val))
            {
                best_cost = cost;
                best_val = curr->value;
            }
        }
        curr = curr->next;
        pos++;
    }
    return (best_val);
}

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

int is_in_chunk(int value, int chunk_index, int chunk_count, int total_size)
{
    int min, max;
    
    get_chunk_range(chunk_index, chunk_count, total_size, &min, &max);
    
    return (value >= min && value <= max);
}

/* Calculate rotation cost and return cheapest direction (1 = ra, -1 = rra, 0 = no rotation needed) */
// int	calculate_rotation_cost(t_stack *stack, int target_value)
// {
//     t_node *current;
//     int rotation_cost;
//     if (!stack || !stack->top)
//         return (-2);
//     rotation_cost = 0;
//     current = stack->top;
//     if (current->value == target_value)
//         return (0);
//     while (current)
//     {
//         if (current->value == target_value)
//             break;
//         rotation_cost++;
//         current = current->next;
//     }
//     if (rotation_cost < stack->size - rotation_cost)
//         return (1);
//     else
//         return (-1);
// }

/* Find maximum value in stack and return its rank */
int	find_max_in_stack(t_stack *stack)
{
    t_node *current;
    int result;
    if (!stack || !stack->top)
        return (-1);
    current = stack->top;
    result = current->value;
    while(current)
    {
        if (current->value > result)
            result = current->value;
        current = current->next;
    }
    return (result);
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
    push_back_to_a(stack_a, stack_b);
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

/* Phase 2: Push elements back from stack B to stack A in sorted order */
void	push_back_to_a(t_stack *stack_a, t_stack *stack_b)
{
    int	max_in_b;
    int rotation_a_cost;

    if (!stack_b || !stack_b->top)
        return ;

    rotation_a_cost = 0;
    while (stack_b->top)
    {
        max_in_b = find_max_in_stack(stack_b);
        rotate_to_top(stack_b, max_in_b, 0);  // Safe early-return if -1
        pa(stack_a, stack_b);
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

/* Maintain descending order in stack B when pushing */
void	maintain_descending_order_b(t_stack *stack_b, int value)
{
    t_node *current;
    int position;
    int target_value;
    int forward_cost;
    int reverse_cost;
    int rotation_count;
    
    if (!stack_b || stack_b->size == 0)
        return;
    
    if (value > stack_b->top->value)
        return;
    
    current = stack_b->top;
    position = 0;
    target_value = -1;
    
    while (current)
    {
        if (current->value <= value)
        {
            target_value = current->value;
            break;
        }
        position++;
        current = current->next;
    }
    
    if (target_value == -1)
        return;
    
    forward_cost = position;
    reverse_cost = stack_b->size - position;
    
    if (forward_cost <= reverse_cost)
    {
        rotation_count = forward_cost;
        while (rotation_count-- > 0)
            rb(stack_b);
    }
    else
    {
        rotation_count = reverse_cost;
        while (rotation_count-- > 0)
            rrb(stack_b);
    }
}

