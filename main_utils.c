#include "push_swap.h"

void	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = NULL;
	stack_a->size = 0;
	stack_b->top = NULL;
	stack_b->size = 0;
}

void	decide_sort(t_stack *stack_a, t_stack *stack_b, int size)
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

int	handle_error(void)
{
	write(2, "Error\n", 6);
	return (1);
}

void	free_stack(t_stack *stack)
{
	t_node	*current;
	t_node	*next;

	if (!stack)
		return ;
	current = stack->top;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->top = NULL;
	stack->size = 0;
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
