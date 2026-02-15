#include "push_swap.h"

void	get_three_values(t_stack *stack_a, int *first, int *second, int *third)
{
	*first = stack_a->top->value;
	*second = stack_a->top->next->value;
	*third = stack_a->top->next->next->value;
}

void	apply_three_sort(t_stack *stack_a, int first, int second, int third)
{
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

int	find_closest_pos(t_stack *stack_a, int min1, int min2)
{
    int pos1;
    int pos2;
    int closest_pos;

    pos1 = get_position_in_stack(stack_a, min1);
    pos2 = get_position_in_stack(stack_a, min2);
    closest_pos = pos1;
    if (pos2 != -1 && (pos1 == -1 || pos2 < pos1))
        closest_pos = pos2;
    return (closest_pos);
}

void	rotate_to_closest_min(t_stack *stack_a, int min1, int min2)
{
    int closest_pos;

    closest_pos = find_closest_pos(stack_a, min1, min2);
    if (closest_pos <= stack_a->size / 2)
        ra(stack_a);
    else
        rra(stack_a);
}

void	finalize_stack_b(t_stack *stack_a, t_stack *stack_b)
{
    if (stack_b->size == 2 && stack_b->top->value < stack_b->top->next->value)
        sb(stack_b);
    while (stack_b->size > 0)
        pa(stack_a, stack_b);
}
