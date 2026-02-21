#include "push_swap.h"

static void	swap(t_stack *stack)
{
	t_node	*tmp;

	if (!stack || !stack->top || !stack->top->next)
		return ;
	tmp = stack->top;
	stack->top = stack->top->next;
	tmp->next = stack->top->next;
	stack->top->next = tmp;
}

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
