#include "push_swap.h"

static int calculate_position_cost(int pos, int stack_size)
{
    int cost;

    cost = pos;
    if (pos > stack_size - pos)
        cost = stack_size - pos;
    return (cost);
}

static void update_best_if_needed(int cost, int value, int *best_cost, int *best_val)
{
    if (cost < *best_cost || (cost == *best_cost && value > *best_val))
    {
        *best_cost = cost;
        *best_val = value;
    }
}

static int find_best(t_stack *stack, t_node *curr, int min_val, int max_val)
{
    int pos;
    int cost;
    int best_cost;
    int best_val;

    best_val = -1;
    pos = 0;
    best_cost = stack->size + 1;
    while (curr)
    {
        if (curr->value >= min_val && curr->value <= max_val)
        {
            cost = calculate_position_cost(pos, stack->size);
            update_best_if_needed(cost, curr->value, &best_cost, &best_val);
        }
        curr = curr->next;
        pos++;
    }
    return (best_val);
}

/**
* Finds the element in the chunk range (min_val to max_val) that is cheapest to move to the top.
* If multiple have the same cost, it picks the largest value.
* @param stack -> stack to search
* @param min_val -> low border of the chunk
* @param max_val -> high border of the chunk
* @returns {Number} cheapest element & largest (value) element in chunk 
*/
int find_largest_cheapest_in_chunk(t_stack *stack, int min_val, int max_val)
{
    t_node *curr;

    if (!stack || !stack->top)
        return (-1);
    curr = stack->top;
    
    return (find_best(stack, curr, min_val, max_val));
}