#include "push_swap.h"

int	get_position_in_stack(t_stack *stack, int target_value)
{
	int		distance;
	t_node	*current;

	if (!stack || !stack->top)
		return (-1);
	distance = 0;
	current = stack->top;
	while (current)
	{
		if (current->value == target_value)
			return (distance);
		distance++;
		current = current->next;
	}
	return (-1);
}

static void	perform_rotations(t_stack *stack, int cost, int dir, int is_a)
{
	while (cost > 0)
	{
		cost--;
		if (dir == 1)
		{
			if (is_a == 1)
				ra(stack);
			else
				rb(stack);
		}
		else
		{
			if (is_a == 1)
				rra(stack);
			else
				rrb(stack);
		}
	}
}

void	rotate_to_top(t_stack *stack, int target_value, int is_stack_a)
{
	int	pos;
	int	dir;
	int	cost;

	if (!stack || !stack->top)
		return ;
	pos = get_position_in_stack(stack, target_value);
	if (pos == -1 || pos == 0)
		return ;
	calc_dir_cost(pos, stack->size, &dir, &cost);
	perform_rotations(stack, cost, dir, is_stack_a);
}

void	execute_move(t_stack *a, t_stack *b, t_move *move)
{
	int	common;

	common = 0;
	if (move->a_dir == move->b_dir && move->a_dir != 0)
	{
		common = move->a_cost;
		if (move->b_cost < common)
			common = move->b_cost;
		do_common_rotations(a, b, common, move->a_dir);
		move->a_cost -= common;
		move->b_cost -= common;
	}
	do_a_rotations(a, move->a_cost, move->a_dir);
	do_b_rotations(b, move->b_cost, move->b_dir);
}

void	push_back_to_a(t_stack *a, t_stack *b)
{
	t_move	move;

	while (b->top)
	{
		find_cheapest_move(a, b, &move);
		execute_move(a, b, &move);
		pa(a, b);
	}
}
