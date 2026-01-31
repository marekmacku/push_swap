#include "push_swap.h"

void decide_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
    if (is_sorted(stack_a))
        return ;
    if (size == 2)
    {
        if (stack_a->top->value > stack_a->top->next->value)
            sa(stack_a);
    }
    else if (size == 3)
        sort_for_three(stack_a);
    else if (size == 4)
        sort_for_four(stack_a, stack_b);
    else if (size == 5)
        sort_for_five(stack_a, stack_b);
}

int handle_error()
{
    write(2, "Error\n", 6);
    return (1);
}
