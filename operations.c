#include "push_swap.h"

void	sa(t_stack *a)
{
    swap(a);
    write(1, "sa\n", 3);
}

void	sb(t_stack *b)
{
    swap(b);
    write(1, "sb\n", 3);
}

void	ss(t_stack *a, t_stack *b)
{
    swap(a);
    swap(b);
    write(1, "ss\n", 3);
}

void	pa(t_stack *a, t_stack *b)
{
    t_node	*node;
    
    if (!b || !b->top)
        return;
    node = b->top;
    pop(&b);
    push(&a, node);
    write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
    t_node	*node;
    
    if (!a || !a->top)
        return;
    node = a->top;
    pop(&a);
    push(&b, node);
    write(1, "pb\n", 3);
}