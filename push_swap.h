#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

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

#endif