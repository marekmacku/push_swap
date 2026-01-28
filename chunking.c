#include "push_swap.h"

int find_largest_cheapest_in_chunk(t_stack *stack, int min_val, int max_val)
{
    t_node *curr;
    int     best_cost;
    int     best_val;
    int     pos;
    int     cost;

    if (!stack || !stack->top)
        return (-1);
    best_cost = stack->size + 1;
    best_val = -1;
    curr = stack->top;
    pos = 0;
    while (curr)
    {
        if (curr->value >= min_val && curr->value <= max_val)
        {
            cost = pos;
            if (pos > stack->size - pos)
                cost = stack->size - pos;
            if (cost < best_cost || (cost == best_cost && curr->value > best_val))
            {
                best_cost = cost;
                best_val = curr->value;
            }
        }
        curr = curr->next;
        pos++;
    }
    return (best_val);
}

int calculate_chunk_count(int size)
{
    if (size <= 16)
        return 1;
    else if (size <= 100)
        return 5;  // ~20 per chunk
    else if (size <= 500)
        return 11; // ~45 per chunk
    else
        return size / 50;
}

void get_chunk_range(int chunk_index, int chunk_count, int total_size, int *min, int *max)
{
    int chunk_size;
    
    chunk_size = total_size / chunk_count;
    *min = chunk_index * chunk_size;
    
    if (chunk_index == chunk_count - 1)
        *max = total_size - 1;
    else
        *max = *min + chunk_size - 1;
}

int is_in_chunk(int value, int chunk_index, int chunk_count, int total_size)
{
    int min, max;
    
    get_chunk_range(chunk_index, chunk_count, total_size, &min, &max);
    
    return (value >= min && value <= max);
}

/* Calculate rotation cost and return cheapest direction (1 = ra, -1 = rra, 0 = no rotation needed) */
// int	calculate_rotation_cost(t_stack *stack, int target_value)
// {
//     t_node *current;
//     int rotation_cost;
//     if (!stack || !stack->top)
//         return (-2);
//     rotation_cost = 0;
//     current = stack->top;
//     if (current->value == target_value)
//         return (0);
//     while (current)
//     {
//         if (current->value == target_value)
//             break;
//         rotation_cost++;
//         current = current->next;
//     }
//     if (rotation_cost < stack->size - rotation_cost)
//         return (1);
//     else
//         return (-1);
// }

/* Find maximum value in stack and return its rank */
int	find_max_in_stack(t_stack *stack)
{
    t_node *current;
    int result;
    if (!stack || !stack->top)
        return (-1);
    current = stack->top;
    result = current->value;
    while(current)
    {
        if (current->value > result)
            result = current->value;
        current = current->next;
    }
    return (result);
}

/* Find position of a value in stack (distance from top) */
int	get_position_in_stack(t_stack *stack, int target_value)
{
    int distance;
    t_node *current;
    if (!stack || !stack->top)
        return  (-1);
    distance = 0;
    current = stack->top;
    while(current)
    {
        if (current->value == target_value)
            return (distance);
        distance++;
        current = current->next;
    }
    return (-1);
}

/* Main function to sort large stacks using chunk-based algorithm */
void	sort_large(t_stack *stack_a, t_stack *stack_b, int size)
{
    int chunk_count;
    
    if (!stack_a || !stack_a->top)
        return ;
    
    chunk_count = calculate_chunk_count(size);
    push_chunks_to_b(stack_a, stack_b, chunk_count, size);
    push_back_to_a_optimized(stack_a, stack_b);
}

/* Phase 1: Push chunks to stack B sequentially */
void	push_chunks_to_b(t_stack *stack_a, t_stack *stack_b, int chunk_count, int total_size)
{
    int	chunk_idx;
    int	min_val;
    int	max_val;
    int	target;
    int	chunk_target_size;
    int	pushed;

    if (!stack_a || !stack_a->top)
        return ;
    chunk_idx = chunk_count - 1;  // START FROM HIGHEST CHUNK (largest values first)
    while (chunk_idx >= 0 && stack_a->size > 0)
    {
        get_chunk_range(chunk_idx, chunk_count, total_size, &min_val, &max_val);
        chunk_target_size = total_size / chunk_count;
        if (chunk_idx == chunk_count - 1)
            chunk_target_size += total_size % chunk_count;
        pushed = 0;
        while (pushed < chunk_target_size && stack_a->size > 0)
        {
            target = find_largest_cheapest_in_chunk(stack_a, min_val, max_val);
            if (target == -1)
                break ;
            rotate_to_top(stack_a, target, 1);
            pb(stack_a, stack_b);
            pushed++;
        }
        chunk_idx--;
    }
}

/* Phase 2: Push elements back from stack B to stack A in sorted order */
void	push_back_to_a(t_stack *stack_a, t_stack *stack_b)
{
    int	max_in_b;

    if (!stack_b || !stack_b->top)
        return ;

    while (stack_b->top)
    {
        max_in_b = find_max_in_stack(stack_b);
        rotate_to_top(stack_b, max_in_b, 0);  // Safe early-return if -1
        pa(stack_a, stack_b);
    }
}

/* Rotate stack to bring target value to top using cheapest direction */
void	rotate_to_top(t_stack *stack, int target_value, int is_stack_a)
{
    int	pos;
    int	ra_cost;
    int	rra_cost;

    if (!stack || !stack->top)
        return ;
    pos = get_position_in_stack(stack, target_value);
    if (pos == -1 || pos == 0)
        return ;
    ra_cost = pos;
    rra_cost = stack->size - pos;
    if (ra_cost <= rra_cost)
    {
        while (ra_cost > 0)
        {
            ra_cost--;
            if (is_stack_a == 1)
                ra(stack);
            else
                rb(stack);
        }
    }
    else
    {
        while (rra_cost > 0)
        {
            rra_cost--;
            if (is_stack_a == 1)
                rra(stack);
            else
                rrb(stack);
        }
    }
}

/* Maintain descending order in stack B when pushing */
void	maintain_descending_order_b(t_stack *stack_b, int value)
{
    t_node *current;
    int position;
    int target_value;
    int forward_cost;
    int reverse_cost;
    int rotation_count;
    
    if (!stack_b || stack_b->size == 0)
        return;
    
    if (value > stack_b->top->value)
        return;
    
    current = stack_b->top;
    position = 0;
    target_value = -1;
    
    while (current)
    {
        if (current->value <= value)
        {
            target_value = current->value;
            break;
        }
        position++;
        current = current->next;
    }
    
    if (target_value == -1)
        return;
    
    forward_cost = position;
    reverse_cost = stack_b->size - position;
    
    if (forward_cost <= reverse_cost)
    {
        rotation_count = forward_cost;
        while (rotation_count-- > 0)
            rb(stack_b);
    }
    else
    {
        rotation_count = reverse_cost;
        while (rotation_count-- > 0)
            rrb(stack_b);
    }
}

// --------- --------- --------- OPTIMIZED WAY  --------- --------- ---------

// Find where value from B should be inserted in sorted A
int     find_target_position(t_stack *stack_a, int value)
{
    int     best_val;
    int     target_pos;
    int     pos;
    t_node  *current;

    if (!stack_a || !stack_a->top)
        return (0);
    best_val = stack_a->size;
    target_pos = -1;
    pos = 0;
    current = stack_a->top;
    while (current)
    {
        if (current->value > value && current->value < best_val)
        {
            best_val = current->value;
            target_pos = pos;
        }
        current = current->next;
        pos++;
    }
    if (target_pos == -1)
        return (get_position_in_stack(stack_a, find_min(stack_a)));
    return (target_pos);
}

int max(int a, int b)
{
    if (a > b)
        return  (a);
    return  (b);
}

// Calculate total cost for moving element at b_pos to its target in A
// Returns the cost considering rr/rrr savings
int     calculate_move_cost(t_stack *stack_a, t_stack *stack_b, int b_pos, int a_target_pos)
{
    int b_direction;
    int a_direction;
    int a_cost;
    int b_cost;

    b_direction = 0;
    a_direction = 0;
    a_cost = 0;
    b_cost = 0;

    if (b_pos <= stack_b->size / 2)
    {
        b_direction = 1;
        b_cost = b_pos;
    }
    else
    {
        b_direction = -1;
        b_cost = stack_b->size - b_pos;
    }
    if (a_target_pos <= stack_a->size / 2)
    {
        a_direction = 1;
        a_cost = a_target_pos;
    }
    else
    {
        a_direction = -1;
        a_cost = stack_a->size - a_target_pos;
    }
    if (a_direction == b_direction)
        return (max(a_cost, b_cost));
    return (a_cost + b_cost);
}

// Find the cheapest element in B and store move info
// You can use a struct or pass pointers to store: b_pos, a_pos, directions
static void calc_dir_cost(int pos, int size, int *dir, int *cost)
{
    if (pos <= size / 2)
    {
        *dir = 1;
        *cost = pos;
    }
    else
    {
        *dir = -1;
        *cost = size - pos;
    }
}

static void update_best_move(t_move *move, int b_pos, int a_pos,
    int b_cost, int a_cost, int b_dir, int a_dir, int total_cost)
{
    move->b_pos = b_pos;
    move->a_pos = a_pos;
    move->b_cost = b_cost;
    move->a_cost = a_cost;
    move->b_dir = b_dir;
    move->a_dir = a_dir;
    move->cost = total_cost;
}

static void check_and_update_move(t_stack *stack_a, t_stack *b,
    t_move *move, int b_pos, int *best_cost, int value)
{
    int target_pos;
    int total_cost;
    int b_dir;
    int a_dir;
    int b_cost;
    int a_cost;
    
    target_pos = find_target_position(stack_a, value);
    calc_dir_cost(b_pos, b->size, &b_dir, &b_cost);
    calc_dir_cost(target_pos, stack_a->size, &a_dir, &a_cost);
    total_cost = calculate_move_cost(stack_a, b, b_pos, target_pos);
    if (total_cost < *best_cost)
    {
        *best_cost = total_cost;
        update_best_move(move, b_pos, target_pos, b_cost,
            a_cost, b_dir, a_dir, total_cost);
    }
}

void find_cheapest_move(t_stack *stack_a, t_stack *b, t_move *move)
{
    t_node *current_b;
    int b_pos;
    int best_cost;
    
    current_b = b->top;
    b_pos = 0;
    best_cost = INT_MAX;
    while (current_b) 
    {
        check_and_update_move(stack_a, b, move, b_pos,
            &best_cost, current_b->value);
        current_b = current_b->next;
        b_pos++;
    }
}

static void do_common_rotations(t_stack *a, t_stack *b, int count, int dir)
{
    while (count > 0)
    {
        if (dir == 1)
            rr(a, b);
        else
            rrr(a, b);
        count--;
    }
}

static void do_a_rotations(t_stack *a, int cost, int dir)
{
    while (cost > 0)
    {
        if (dir == 1)
            ra(a);
        else
            rra(a);
        cost--;
    }
}

static void do_b_rotations(t_stack *b, int cost, int dir)
{
    while (cost > 0)
    {
        if (dir == 1)
            rb(b);
        else
            rrb(b);
        cost--;
    }
}

void execute_move(t_stack *a, t_stack *b, t_move *move)
{
    int common_rotations;
    
    if (move->a_dir == move->b_dir && move->a_dir != 0)
    {
        common_rotations = (move->a_cost < move->b_cost)
            ? move->a_cost : move->b_cost;
        do_common_rotations(a, b, common_rotations, move->a_dir);
        move->a_cost -= common_rotations;
        move->b_cost -= common_rotations;
    }
    do_a_rotations(a, move->a_cost, move->a_dir);
    do_b_rotations(b, move->b_cost, move->b_dir);
}

void push_back_to_a_optimized(t_stack *a, t_stack *b)
{
    t_move move;
    
    while (b->top)
    {
        find_cheapest_move(a, b, &move);
        execute_move(a, b, &move);
        pa(a, b);
    }
}

