#include "push_swap.h"

static void	set_move_data(t_move *move, t_element_info *elem,
	t_rotation_data *rot, int target_pos)
{
	move->a_pos = elem->b_pos;
	move->b_pos = target_pos;
	move->a_cost = rot->a_cost;
	move->a_dir = rot->a_dir;
	move->b_cost = rot->b_cost;
	move->b_dir = rot->b_dir;
}

static void	check_and_update_push(t_move_context *ctx, t_element_info *elem)
{
	int				target_pos;
	int				total_cost;
	t_rotation_data	rot;

	target_pos = find_target_in_b(ctx->stack_b, elem->value);
	calc_dir_cost(elem->b_pos, ctx->stack_a->size, &rot.a_dir, &rot.a_cost);
	calc_dir_cost(target_pos, ctx->stack_b->size, &rot.b_dir, &rot.b_cost);
	total_cost = total_rotation_costs(rot.a_cost, rot.b_cost,
			rot.a_dir, rot.b_dir);
	if (total_cost < *ctx->best_cost)
	{
		*ctx->best_cost = total_cost;
		set_move_data(ctx->move, elem, &rot, target_pos);
		ctx->move->cost = total_cost;
	}
}

void	find_cheapest_push_to_b(t_stack *a, t_stack *b, t_move *move)
{
	t_node			*current;
	int				pos;
	int				best_cost;
	t_element_info	elem;
	t_move_context	ctx;

	ctx.stack_a = a;
	ctx.stack_b = b;
	ctx.move = move;
	ctx.best_cost = &best_cost;
	current = a->top;
	pos = 0;
	best_cost = INT_MAX;
	while (current)
	{
		elem.b_pos = pos;
		elem.value = current->value;
		check_and_update_push(&ctx, &elem);
		current = current->next;
		pos++;
	}
}
