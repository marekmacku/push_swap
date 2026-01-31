#include "push_swap.h"

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

static void	cleanup_split(char **result, int idx)
{
	while (idx > 0)
		free(result[--idx]);
	free(result);
}

static int	extract_all_words(char **result, char const *s, char c, int word_count)
{
	int		pos;
	int		idx;

	pos = 0;
	idx = 0;
	while (idx < word_count)
	{
		result[idx] = extract_word(s, c, &pos);
		if (!result[idx])
		{
			cleanup_split(result, idx);
			return (0);
		}
		idx++;
	}
	result[idx] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = malloc((word_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (!extract_all_words(result, s, c, word_count))
		return (NULL);
	return (result);
}