#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top || !stack->top->next)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

void sort_for_three(t_stack *stack_a)
{
    int first = stack_a->top->value;
    int second = stack_a->top->next->value;
    int third =  stack_a->top->next->next->value;

    if (is_sorted(stack_a))
        return ;
    if (first < second && first < third && second > third)
    {
        sa(stack_a);
        ra(stack_a);
    }
    else if (second < first && second < third && first < third)
        sa(stack_a);
    else if (first < second && second > third && first > third)
        rra(stack_a);
    else if (first > second && second < third && first > third)
        ra(stack_a);
    else if (first > second && second > third)
    {
        sa(stack_a);
        rra(stack_a);
    }
}

int find_min(t_stack *stack)
{
    t_node *current;
    int min;
    
    if (!stack || !stack->top)
        return (0);
    current = stack->top;
    min = current->value;
    while (current)
    {
        if (current->value < min)
            min = current->value;
        current = current->next;
    }
    return (min);
}

int find_second_min(t_stack *stack, int min1)
{
    t_node *current;
    int min2;
    int found;

    if (!stack || !stack->top)
        return (0);
    current = stack->top;
    found = 0;
    while (current)
    {
        if (current->value != min1)
        {
            if (!found)
            {
                min2 = current->value;
                found = 1;
            }
            else if (current->value < min2)
            {
                min2 = current->value;
            }
        }
        current = current->next;
    }
    return (min2);
}

void sort_for_four(t_stack *stack_a, t_stack *stack_b)
{
    int min, pos;

    if (!stack_a)
        return ;
    min = find_min(stack_a);
    pos = get_position_in_stack(stack_a, min);
    
    // Use optimal rotation direction
    while (stack_a->top->value != min)
    {
        if (pos <= stack_a->size / 2)
            ra(stack_a);
        else
            rra(stack_a);
    }
    pb(stack_a, stack_b);
    sort_for_three(stack_a);
    pa(stack_a, stack_b);
}

void sort_for_five(t_stack *stack_a, t_stack *stack_b)
{
    int min1, min2, pos1, pos2, closest_pos;

    if (!stack_a)
        return ;
    min1 = find_min(stack_a);
    min2 = find_second_min(stack_a, min1);
    while (stack_a->size > 3)
    {
        if (stack_a->top->value == min1 || stack_a->top->value == min2)
            pb(stack_a, stack_b);
        else
        {
            pos1 = get_position_in_stack(stack_a, min1);
            pos2 = get_position_in_stack(stack_a, min2);
            
            // Find which minimum is closer
            closest_pos = pos1;
            if (pos2 != -1 && (pos1 == -1 || pos2 < pos1))
                closest_pos = pos2;
            
            // Choose optimal rotation direction
            if (closest_pos <= stack_a->size / 2)
                ra(stack_a);
            else
                rra(stack_a);
        }
    }
    sort_for_three(stack_a);
    if (stack_b->size == 2 && stack_b->top->value > stack_b->top->next->value)
        sb(stack_b);
    while (stack_b->size > 0)
        pa(stack_a, stack_b);
}