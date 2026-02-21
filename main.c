#include "push_swap.h"

static char	**prepare_input(int argc, char **argv, int *is_split)
{
	*is_split = 0;
	if (argc == 2)
	{
		*is_split = 1;
		return (ft_split(argv[1], ' '));
	}
	return (&argv[1]);
}

static int	validate_and_parse(char **input, t_stack *stack_a)
{
	if (!input || !input[0])
		return (-1);
	if (!parse_input(input, stack_a))
	{
		handle_error();
		return (0);
	}
	if (has_duplicates(stack_a))
	{
		handle_error();
		return (0);
	}
	return (1);
}

static void	cleanup(t_stack *a, t_stack *b, char **input, int is_split)
{
	free_stack(a);
	free_stack(b);
	if (is_split)
		free_split(input);
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

int	main(int argc, char **argv)
{
	char	**input;
	t_stack	stack_a;
	t_stack	stack_b;
	int		is_split;
	int		ret;

	if (argc == 1)
		return (0);
	init_stacks(&stack_a, &stack_b);
	input = prepare_input(argc, argv, &is_split);
	ret = validate_and_parse(input, &stack_a);
	if (ret <= 0)
	{
		cleanup(&stack_a, &stack_b, input, is_split);
		if (ret == 0)
			return (1);
		return (0);
	}
	execute_sort(&stack_a, &stack_b);
	cleanup(&stack_a, &stack_b, input, is_split);
	return (0);
}
