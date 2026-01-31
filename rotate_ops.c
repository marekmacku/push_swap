#include "push_swap.h"

void	rotate(t_stack *stack)
{
    t_node	*first;
    t_node	*tmp;

    if (!stack || !stack->top || !stack->top->next)
        return;
    first = stack->top;
    stack->top = stack->top->next;
    tmp = stack->top;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = first;
    first->next = NULL;
}

void	ra(t_stack *a)
{
    rotate(a);
    write(1, "ra\n", 3);
}

void	rb(t_stack *b)
{
    rotate(b);
    write(1, "rb\n", 3);
}

void	rr(t_stack *a, t_stack *b)
{
    rotate(a);
    rotate(b);
    write(1, "rr\n", 3);
}
