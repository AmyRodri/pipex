#include "libft.h"
#include <stdlib.h>

static int	count_args(const char *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] && (s[i] == c || s[i] == '\t'))
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i])
		{
			if (quote)
			{
				if (s[i] == quote)
					quote = 0;
			}
			else if (s[i] == '\'')
				quote = '\'';
			else if (s[i] == c || s[i] == '\t')
				break ;
			i++;
		}
	}
	return (count);
}

static char	*copy_arg(const char *s, int *idx, char c)
{
	int		start;
	int		len;
	char	*arg;
	char	quote;
	int		j;

	while (s[*idx] && (s[*idx] == c || s[*idx] == '\t'))
		(*idx)++;
	start = *idx;
	quote = 0;
	while (s[*idx])
	{
		if (quote)
		{
			if (s[*idx] == quote)
				quote = 0;
		}
		else if (s[*idx] == '\'')
			quote = '\'';
		else if (s[*idx] == c || s[*idx] == '\t')
			break ;
		(*idx)++;
	}
	len = *idx - start;
	arg = malloc(sizeof(char) * (len + 1));
	if (!arg)
		return (NULL);
	j = 0;
	while (start < *idx)
	{
		if (s[start] != '\'')
			arg[j++] = s[start];
		start++;
	}
	arg[j] = '\0';
	return (arg);
}

char	**ft_split_quotes(const char *s, char c)
{
	char	**split;
	int		count;
	int		i;
	int		idx;

	if (!s)
		return (NULL);
	count = count_args(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	i = 0;
	idx = 0;
	while (i < count)
	{
		split[i] = copy_arg(s, &idx, c);
		if (!split[i])
		{
			while (--i >= 0)
				free(split[i]);
			free(split);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
