#include "push_swap.h"

static void	reverse_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*tmp;
	t_node	*second_to_last;

	if (!stack || !stack->top || !stack->top->next)
		return ;
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

void	rrr(t_stack *a, t_stack *b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}

void	rra(t_stack *a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

void	rrb(t_stack *b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}
