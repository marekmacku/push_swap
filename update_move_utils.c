#include "push_swap.h"

// Find where value from B should be inserted in sorted A
int     find_target_position(t_stack *stack_a, int value)
{
    int     best_val;
    int     target_pos;
    int     pos;
    t_node  *current;

    if (!stack_a || !stack_a->top)
        return (0);
    best_val = stack_a->size;
    target_pos = -1;
    pos = 0;
    current = stack_a->top;
    while (current)
    {
        if (current->value > value && current->value < best_val)
        {
            best_val = current->value;
            target_pos = pos;
        }
        current = current->next;
        pos++;
    }
    if (target_pos == -1)
        return (get_position_in_stack(stack_a, find_min(stack_a)));
    return (target_pos);
}

// Find the cheapest element in B and store move info
// You can use a struct or pass pointers to store: b_pos, a_pos, directions
void calc_dir_cost(int pos, int size, int *dir, int *cost)
{
    if (pos <= size / 2)
    {
        *dir = 1;
        *cost = pos;
    }
    else
    {
        *dir = -1;
        *cost = size - pos;
    }
}

// Combine rotation costs for both stacks, optimizing with rr/rrr when directions match
int     total_rotation_costs(int a_cost, int b_cost, int a_dir, int b_dir)
{
    if (a_dir == b_dir)
    {
        if (a_cost > b_cost)
            return (a_cost);
        return (b_cost);
    }
    return (a_cost + b_cost);
}