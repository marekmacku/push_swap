#include "push_swap.h"

static void	init_stacks(t_stack *stack_a, t_stack *stack_b)
{
	stack_a->top = NULL;
	stack_a->size = 0;
	stack_b->top = NULL;
	stack_b->size = 0;
}

static char	**prepare_input(int argc, char **argv)
{
	if (argc == 2)
		return (ft_split(argv[1], ' '));
	return (&argv[1]);
}

static int	validate_and_parse(char **input, t_stack *stack_a)
{
	if (!parse_input(input, stack_a))
		return (0);
	if (has_duplicates(stack_a))
	{
		handle_error();
		return (0);
	}
	return (1);
}

static void	execute_sort(t_stack *stack_a, t_stack *stack_b)
{
	if (stack_a->size <= 5)
		decide_sort(stack_a, stack_b, stack_a->size);
	else
	{
		normalize(stack_a);
		sort_large(stack_a, stack_b, stack_a->size);
	}
}

int main(int argc, char **argv)
{
	char	**input;
	t_stack	stack_a;
	t_stack	stack_b;

	if (argc == 1)
		return (0);
	init_stacks(&stack_a, &stack_b);
	input = prepare_input(argc, argv);
	if (!validate_and_parse(input, &stack_a))
		return (1);
	execute_sort(&stack_a, &stack_b);
	return (0);
}
