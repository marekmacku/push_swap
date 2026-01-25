#include "push_swap.h"

static void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap_int(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_int(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void	quicksort(int *arr, int low, int high)
{
	int	pivot_index;

	if (low < high)
	{
		pivot_index = partition(arr, low, high);
		quicksort(arr, low, pivot_index - 1);
		quicksort(arr, pivot_index + 1, high);
	}
}

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

void	normalize(t_stack *stack_a)
{
	int		*arr;
	t_node	*current;
	int		i;
	int		rank;

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
	while (current)
	{
		rank = binary_search_rank(arr, stack_a->size, current->value);
		if (rank != -1)
			current->value = rank;
		current = current->next;
	}
	free(arr);
}