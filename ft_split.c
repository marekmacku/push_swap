#include <stdlib.h>
#include <stdio.h>

char *fill_string(char *dest, char const *src, int len)
{
    int i;

    i = 0;
    while(i < len)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char *allocate_string(int size)
{
    char *result;

    result = malloc(size);
    if (result == NULL)
        return (NULL);
    return (result);
}

char    **ft_split(char const *s, char c)
{
    char **result;
    int i;
    int break_count;
    int y;

    i = 0;
    break_count = 0;
    while (s[i])
    {
        if (s[i] == c)
            break_count++;
        i++;
    }
    result = malloc(break_count * sizeof(char *));
    if (result == NULL)
        return (NULL);
    i = 0;
    break_count = 0;
    y = 0;
    while (s[i])
    {
        if (s[i] == c)
        {
            result[y] = allocate_string(i - y + 1);
            result[y] = fill_string(result[y], &s[i], i - y);
            y++;
        }
        i++;
    }
    return (result);
}

// Helper to free the array returned by ft_split
void free_split(char **arr)
{
    int i = 0;

    if (!arr)
        return;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

int main(void)
{
    char *str = "Hello,,World,this,is,,42";
    char delimiter = ',';

    char **result = ft_split(str, delimiter);

    if (!result)
    {
        printf("ft_split returned NULL\n");
        return 1;
    }

    printf("Input string: \"%s\"\n", str);
    printf("Delimiter: '%c'\n\n", delimiter);

    // Print each resulting string
    int i = 0;
    while (result[i])
    {
        printf("result[%d] = \"%s\"\n", i, result[i]);
        i++;
    }

    // Free everything
    free_split(result);

    return 0;
}