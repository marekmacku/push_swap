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

static int	count_words(char const *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*extract_word(char const *s, char c, int *start)
{
	int		len;
	char	*word;
	int		i;

	while (s[*start] == c)
		(*start)++;
	if (s[*start] == '\0')
		return (NULL);
	len = 0;
	while (s[*start + len] != c && s[*start + len] != '\0')
		len++;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[*start + i];
		i++;
	}
	word[i] = '\0';
	*start += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		pos;
	int		idx;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	pos = 0;
	idx = 0;
	while (idx < word_count)
	{
		result[idx] = extract_word(s, c, &pos);
		if (!result[idx])
		{
			while (idx > 0)
				free(result[--idx]);
			free(result);
			return (NULL);
		}
		idx++;
	}
	result[idx] = NULL;
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

// int main(void)
// {
//     char *str = "Hello,,World,this,is,,42";
//     char delimiter = ',';

//     char **result = ft_split(str, delimiter);

//     if (!result)
//     {
//         printf("ft_split returned NULL\n");
//         return 1;
//     }

//     printf("Input string: \"%s\"\n", str);
//     printf("Delimiter: '%c'\n\n", delimiter);

//     // Print each resulting string
//     int i = 0;
//     while (result[i])
//     {
//         printf("result[%d] = \"%s\"\n", i, result[i]);
//         i++;
//     }

//     // Free everything
//     free_split(result);

//     return 0;
// }