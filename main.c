#include "push_swap.h"

void decide_sort(t_stack *stack_a, t_stack *stack_b, int size)
{
    if (is_sorted(stack_a))
        return ;
    if (size == 2)
    {
        if (stack_a->top->value > stack_a->top->next->value)
            sa(stack_a);
    }
    else if (size == 3)
        sort_for_three(stack_a);
    else if (size == 4)
        sort_for_four(stack_a, stack_b);
    else if (size == 5)
        sort_for_five(stack_a, stack_b);
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
    
    if (stack_a.size <= 5)
        decide_sort(&stack_a, &stack_b, stack_a.size);
    else
    {
        normalize(&stack_a);
        sort_large(&stack_a, &stack_b,  stack_a.size);
    }
    
    return (0);
}
