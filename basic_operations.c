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

void pop(t_stack **stack)
{
    t_node	*tmp;

    if (!*stack || !(*stack)->top)
        return;
    tmp = (*stack)->top;
    (*stack)->top = (*stack)->top->next;
    free(tmp);
    (*stack)->size--;
}

void	swap(t_stack *stack)
{
    t_node *tmp;

    if (!stack || !stack->top || !stack->top->next)
        return;
    tmp = stack->top;
    stack->top = stack->top->next;
    tmp->next = stack->top->next;
    stack->top->next = tmp;
}

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

void	reverse_rotate(t_stack *stack)
{
    t_node	*first;
    t_node	*tmp;
    t_node	*second_to_last;

    if (!stack || !stack->top || !stack->top->next)
        return;
    first = stack->top;
    tmp = stack->top;
    while (tmp->next != NULL)
    {
        second_to_last = tmp;
        tmp = tmp->next;
    }
    stack->top = tmp;
    tmp->next = first;
    second_to_last->next = NULL;
}