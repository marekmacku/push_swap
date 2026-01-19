#include "push_swap.h"
#include <stdlib.h>
#include <limits.h>

int is_valid_integer_format(char *str)
{
    int i;

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

int has_duplicates(t_stack *stack)
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

int parse_and_validate_int(char *str, int *value)
{
    long long	num;
    int			sign;
    int			i;

    if (!str || !*str)
        return (0);
    num = 0;
    sign = 1;
    i = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (!ft_isdigit(str[i]))
        return (0);
    while (ft_isdigit(str[i]))
    {
        num = num * 10 + (str[i] - '0');
        if ((sign == 1 && num > INT_MAX) || (sign == -1 && num > (long long)INT_MAX + 1))
            return (0);
        i++;
    }
    if (str[i] != '\0')
        return (0);
    num = num * sign;
    if (num < INT_MIN || num > INT_MAX)
        return (0);
    *value = (int)num;
    return (1);
}


t_node *create_node(int value)
{
    t_node *new_node = malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->value = value;
    new_node->next = NULL;
    return (new_node);
}


int parse_input(char **raw_input, t_stack *stack)
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
        push(&stack, new_node);
        i++;
    }
    return (1);
}