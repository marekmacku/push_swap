#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

/* Stack node structure */
typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

/* Stack structure */
typedef struct s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

/* Move info structure for cost-based optimization */
typedef struct s_move
{
	int		b_pos;
	int		a_pos;
	int		b_cost;
	int		a_cost;
	int		b_dir;
	int		a_dir;
	int		cost;
}	t_move;

/* Stack operations */
void	push(t_stack **stack, t_node *node);
void	pop(t_stack **stack);
void	swap(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);

/* Push_swap operations */
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack *a, t_stack *b);
void	pb(t_stack *a, t_stack *b);
void	ra(t_stack *a);
void	rb(t_stack *b);
void	rr(t_stack *a, t_stack *b);
void	rra(t_stack *a);
void	rrb(t_stack *b);
void	rrr(t_stack *a, t_stack *b);

/* Utility functions */
char    **ft_split(char const *s, char c);
int		ft_isdigit(char c);
int		parse_input(char **raw_input, t_stack *stack);
int		has_duplicates(t_stack *stack);

// Sort functions
int		is_sorted(t_stack *stack);
void	sort_for_three(t_stack *stack_a);
void	sort_for_four(t_stack *stack_a, t_stack *stack_b);
void	sort_for_five(t_stack *stack_a, t_stack *stack_b);
int		find_min(t_stack *stack);
int		find_second_min(t_stack *stack, int min1);
void	decide_sort(t_stack *stack_a, t_stack *stack_b, int size);
void	normalize(t_stack *stack_a);

// Chunking functions for large stacks
int		calculate_chunk_count(int size);
void	get_chunk_range(int chunk_index, int chunk_count, int total_size, int *min, int *max);
int		is_in_chunk(int value, int chunk_index, int chunk_count, int total_size);
int		calculate_rotation_cost(t_stack *stack, int target_value);
int		find_max_in_stack(t_stack *stack);
int		get_position_in_stack(t_stack *stack, int target_value);
void	sort_large(t_stack *stack_a, t_stack *stack_b, int size);
void	push_chunks_to_b(t_stack *stack_a, t_stack *stack_b, int chunk_count, int total_size);
void	push_back_to_a(t_stack *stack_a, t_stack *stack_b);
void	rotate_to_top(t_stack *stack, int target_value, int is_stack_a);
void	maintain_descending_order_b(t_stack *stack_b, int value);
// Optimized chunking functions
int		find_target_position(t_stack *stack_a, int value);
int		calculate_move_cost(t_stack *stack_a, t_stack *stack_b, int b_pos, int a_target_pos);
void	find_cheapest_move(t_stack *stack_a, t_stack *b, t_move *move);
void	execute_move(t_stack *a, t_stack *b, t_move *move);
void	push_back_to_a_optimized(t_stack *a, t_stack *b);

#endif