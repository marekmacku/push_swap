#include "push_swap.h"

static int	is_valid_integer_format(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

static t_node	*create_node(int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

static void	append_bottom(t_stack *stack, t_node *node)
{
	t_node	*tmp;

	if (!stack->top)
	{
		stack->top = node;
	}
	else
	{
		tmp = stack->top;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	node->next = NULL;
	stack->size++;
}

int	parse_input(char **raw_input, t_stack *stack)
{
	int		i;
	int		value;
	t_node	*new_node;

	if (!raw_input || !stack)
		return (0);
	stack->top = NULL;
	stack->size = 0;
	i = 0;
	while (raw_input[i])
	{
		if (!is_valid_integer_format(raw_input[i]))
			return (0);
		if (!parse_and_validate_int(raw_input[i], &value))
			return (0);
		new_node = create_node(value);
		if (!new_node)
			return (0);
		append_bottom(stack, new_node);
		i++;
	}
	return (1);
}
