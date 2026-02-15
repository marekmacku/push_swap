#include "push_swap.h"

//**
// Sort for three
//  */
void    sort_for_three(t_stack *stack_a)
{
    int first;
    int second;
    int third;
    
    if (is_sorted(stack_a))
        return ;
    get_three_values(stack_a, &first, &second, &third);
    apply_three_sort(stack_a, first, second, third);
}

//**
// Sort for four
//  */
void sort_for_four(t_stack *stack_a, t_stack *stack_b)
{
    int min;
    int pos;

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

//**
// Sort for five
//  */
void sort_for_five(t_stack *stack_a, t_stack *stack_b)
{
    int min1;
    int min2;

    if (!stack_a)
        return ;
    min1 = find_min(stack_a);
    min2 = find_second_min(stack_a, min1);
    while (stack_a->size > 3)
    {
        if (stack_a->top->value == min1 || stack_a->top->value == min2)
            pb(stack_a, stack_b);
        else
            rotate_to_closest_min(stack_a, min1, min2);
    }
    sort_for_three(stack_a);
    finalize_stack_b(stack_a, stack_b);
}

void	final_rotation(t_stack *stack_a)
{
	int	min;

	if (is_sorted(stack_a))
		return ;
	min = find_min(stack_a);
	rotate_to_top(stack_a, min, 1);
}

void	sort_large(t_stack *stack_a, t_stack *stack_b, int size)
{
	if (!stack_a || !stack_a->top)
		return ;
	(void)size;
	push_all_to_b(stack_a, stack_b);
	sort_for_three(stack_a);
	push_back_to_a(stack_a, stack_b);
	final_rotation(stack_a);
}
