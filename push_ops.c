#include "push_swap.h"

void push(t_stack **stack, t_node *node)
{
    if (!node || !*stack)
        return;
    if ((*stack)->top)
        node->next = (*stack)->top;
    else
        node->next = NULL;
    (*stack)->top = node;
    (*stack)->size++;
}

void	pa(t_stack *a, t_stack *b)
{
    t_node	*node;
    
    if (!b || !b->top)
        return;
    node = b->top;
    b->top = b->top->next;
    b->size--;
    if (a->top)
        node->next = a->top;
    else
        node->next = NULL;
    a->top = node;
    a->size++;
    write(1, "pa\n", 3);
}

void	pb(t_stack *a, t_stack *b)
{
    t_node	*node;
    
    if (!a || !a->top)
        return;
    node = a->top;
    a->top = a->top->next;
    a->size--;
    if (b->top)
        node->next = b->top;
    else
        node->next = NULL;
    b->top = node;
    b->size++;
    write(1, "pb\n", 3);
}