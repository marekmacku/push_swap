#include "push_swap.h"

static void	set_move_positions(t_move *move, int b_pos, int a_pos)
{
	move->b_pos = b_pos;
	move->a_pos = a_pos;
}

static void	set_move_costs(t_move *move, int b_cost, int a_cost, int total)
{
	move->b_cost = b_cost;
	move->a_cost = a_cost;
	move->cost = total;
}

static void	set_move_directions(t_move *move, int b_dir, int a_dir)
{
	move->b_dir = b_dir;
	move->a_dir = a_dir;
}

static void	check_and_update_move(t_move_context *ctx, t_element_info *elem)
{
	int				target_pos;
	int				total_cost;
	t_rotation_data	rot_data;

	target_pos = find_target_position(ctx->stack_a, elem->value);
	calc_dir_cost(elem->b_pos, ctx->stack_b->size,
		&rot_data.b_dir, &rot_data.b_cost);
	calc_dir_cost(target_pos, ctx->stack_a->size,
		&rot_data.a_dir, &rot_data.a_cost);
	total_cost = total_rotation_costs(rot_data.a_cost, rot_data.b_cost,
			rot_data.a_dir, rot_data.b_dir);
	if (total_cost < *ctx->best_cost)
	{
		*ctx->best_cost = total_cost;
		set_move_positions(ctx->move, elem->b_pos, target_pos);
		set_move_costs(ctx->move, rot_data.b_cost,
			rot_data.a_cost, total_cost);
		set_move_directions(ctx->move, rot_data.b_dir, rot_data.a_dir);
	}
}

void	find_cheapest_move(t_stack *stack_a, t_stack *b, t_move *move)
{
	t_node			*current_b;
	int				b_pos;
	int				best_cost;
	t_element_info	elem;
	t_move_context	ctx;

	ctx.stack_a = stack_a;
	ctx.stack_b = b;
	ctx.move = move;
	ctx.best_cost = &best_cost;
	current_b = b->top;
	b_pos = 0;
	best_cost = INT_MAX;
	while (current_b)
	{
		elem.b_pos = b_pos;
		elem.value = current_b->value;
		check_and_update_move(&ctx, &elem);
		current_b = current_b->next;
		b_pos++;
	}
}
