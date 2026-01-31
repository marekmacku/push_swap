#include "push_swap.h"

static int	binary_search_rank(int *arr, int size, int target)
{
	int	left;
	int	right;
	int	mid;

	left = 0;
	right = size - 1;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (arr[mid] == target)
			return (mid);
		else if (arr[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return (-1);
}

static void	assign_ranks(t_node *current, int *arr, t_stack *stack_a)
{
	int rank;

	while (current)
	{
		rank = binary_search_rank(arr, stack_a->size, current->value);
		if (rank != -1)
			current->value = rank;
		current = current->next;
	}
}

void	normalize(t_stack *stack_a)
{
	int		*arr;
	t_node	*current;
	int		i;

	if (!stack_a || !stack_a->top)
		return ;
	arr = malloc(sizeof(int) * stack_a->size);
	if (!arr)
		return ;
	current = stack_a->top;
	i = 0;
	while (current)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	quicksort(arr, 0, stack_a->size - 1);
	current = stack_a->top;
	assign_ranks(current, arr, stack_a);
	free(arr);
}