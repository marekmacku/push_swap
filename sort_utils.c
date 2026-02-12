#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack || !stack->top || !stack->top->next)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

int find_min(t_stack *stack)
{
    t_node *current;
    int min;
    
    if (!stack || !stack->top)
        return (0);
    current = stack->top;
    min = current->value;
    while (current)
    {
        if (current->value < min)
            min = current->value;
        current = current->next;
    }
    return (min);
}

static void	update_min2(int value, int *min2, int *found)
{
    if (!*found)
    {
        *min2 = value;
        *found = 1;
    }
    else if (value < *min2)
        *min2 = value;
}

int find_second_min(t_stack *stack, int min1)
{
    t_node *current;
    int min2;
    int found;

    if (!stack || !stack->top)
        return (0);
    current = stack->top;
    found = 0;
    while (current)
    {
        if (current->value != min1)
            update_min2(current->value, &min2, &found);
        current = current->next;
    }
    return (min2);
}

int	is_circularly_sorted(t_stack *stack)
{
	t_node	*current;
	int		breaks;
	int		first_value;
	int		last_value;

	if (!stack || !stack->top || !stack->top->next)
		return (1);
	breaks = 0;
	current = stack->top;
	first_value = current->value;
	while (current->next)
	{
		if (current->value > current->next->value)
			breaks++;
		current = current->next;
	}
	last_value = current->value;
	if (last_value > first_value)
		breaks++;
	if (breaks <= 1)
		return (1);
	return (0);
}