#include "push_swap.h"

void decide_sort(t_stack *stack_a, int size)
{
    if (size == 2)
    {
        if (stack_a->top > stack_a->top->next)
            ra(stack_a);
        else if (stack_a->top < stack_a->top->next)
            rra(stack_a);
    }
    else if (size == 3)
    {
        
    }
}

static int	is_sorted(t_stack *stack)
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

int main(int argc, char **argv)
{
    char	**input;
    t_stack	stack_a;
    t_stack	stack_b;

    if (argc == 1)
        return (0);
    
    stack_a.top = NULL;
    stack_a.size = 0;
    stack_b.top = NULL;
    stack_b.size = 0;
    
    if (argc == 2)
        input = ft_split(argv[1], ' ');
    else
        input = &argv[1];

    if (!parse_input(input, &stack_a))
    {
        write(2, "Error\n", 6);
        return (1);
    }
    
    if (has_duplicates(&stack_a))
    {
        write(2, "Error\n", 6);
        return (1);
    }
    // TODO: Add sorting logic here
    // sort_stack(&stack_a, &stack_b);
    
    return (0);
}
