#include "push_swap.h"

void	do_common_rotations(t_stack *a, t_stack *b, int count, int dir)
{
	while (count > 0)
	{
		if (dir == 1)
			rr(a, b);
		else
			rrr(a, b);
		count--;
	}
}

void	do_a_rotations(t_stack *a, int cost, int dir)
{
	while (cost > 0)
	{
		if (dir == 1)
			ra(a);
		else
			rra(a);
		cost--;
	}
}

void	do_b_rotations(t_stack *b, int cost, int dir)
{
	while (cost > 0)
	{
		if (dir == 1)
			rb(b);
		else
			rrb(b);
		cost--;
	}
}
