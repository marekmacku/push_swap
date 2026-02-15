#include "push_swap.h"

int	find_max(t_stack *stack)
{
	t_node	*current;
	int		max;

	if (!stack || !stack->top)
		return (0);
	current = stack->top;
	max = current->value;
	while (current)
	{
		if (current->value > max)
			max = current->value;
		current = current->next;
	}
	return (max);
}

static int	find_best_spot_in_b(t_stack *b, int value)
{
	t_node	*current;
	int		best_val;
	int		target_pos;
	int		pos;

	best_val = -1;
	target_pos = -1;
	pos = 0;
	current = b->top;
	while (current)
	{
		if (current->value < value && current->value > best_val)
		{
			best_val = current->value;
			target_pos = pos;
		}
		current = current->next;
		pos++;
	}
	return (target_pos);
}

int	find_target_in_b(t_stack *stack_b, int value)
{
	int	target_pos;

	if (!stack_b || !stack_b->top)
		return (0);
	target_pos = find_best_spot_in_b(stack_b, value);
	if (target_pos == -1)
		return (get_position_in_stack(stack_b, find_max(stack_b)));
	return (target_pos);
}

static void	push_initial_two(t_stack *a, t_stack *b)
{
	pb(a, b);
	pb(a, b);
}

void	push_all_to_b(t_stack *stack_a, t_stack *stack_b)
{
	t_move	move;

	if (stack_a->size <= 3)
		return ;
	push_initial_two(stack_a, stack_b);
	while (stack_a->size > 3)
	{
		find_cheapest_push_to_b(stack_a, stack_b, &move);
		execute_move(stack_a, stack_b, &move);
		pb(stack_a, stack_b);
	}
}
