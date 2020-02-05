#include "minishell.h"

char	*double_quote_allocator(char *s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = (ft_strchr(s + 1, '\"') - (s + 1));
	cmd = ft_strndup(s + 1, i);
	*j += i + 2;
	return (cmd);
}

char	*simple_quote_allocator(char *s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = (ft_strchr(s + 1, '\'') - (s + 1));
	cmd = ft_strndup(s + 1, i);
	*j += i + 2;
	return (cmd);
}

char	*non_special_allocator(char *s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = 0;
	while (s[i] && !ft_strchr(" \t\'\"", s[i]))
		i++;
	cmd = ft_strndup(s + i, i);
	*j += i + 2;
	return (cmd);
}