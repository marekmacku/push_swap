#include "push_swap.h"

static int	parse_sign(char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	parse_number(char *str, int *i, int sign, long long *num)
{
	if (!ft_isdigit(str[*i]))
		return (0);
	while (ft_isdigit(str[*i]))
	{
		*num = *num * 10 + (str[*i] - '0');
		if ((sign == 1 && *num > INT_MAX)
			|| (sign == -1 && *num > (long long)INT_MAX + 1))
			return (0);
		(*i)++;
	}
	return (1);
}

int	parse_and_validate_int(char *str, int *value)
{
	long long	num;
	int			sign;
	int			i;

	if (!str || !*str)
		return (0);
	num = 0;
	i = 0;
	sign = parse_sign(str, &i);
	if (!parse_number(str, &i, sign, &num))
		return (0);
	if (str[i] != '\0')
		return (0);
	num = num * sign;
	if (num < INT_MIN || num > INT_MAX)
		return (0);
	*value = (int)num;
	return (1);
}

int	has_duplicates(t_stack *stack)
{
	t_node	*current;
	t_node	*checker;

	if (!stack || !stack->top)
		return (0);
	current = stack->top;
	while (current)
	{
		checker = current->next;
		while (checker)
		{
			if (current->value == checker->value)
				return (1);
			checker = checker->next;
		}
		current = current->next;
	}
	return (0);
}
