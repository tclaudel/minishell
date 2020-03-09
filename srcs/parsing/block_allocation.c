#include "minishell.h"

char	*simple_quote_allocator(char *s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = *j;
	i = ft_charpos(s + *j + 1, '\'');
	cmd = ft_strndup(s + *j + 1, i);
	*j += i + 2;
	return (cmd);
}

char	*double_quote_allocator(char **s, size_t *j)
{
	char	*cmd;
	char	*tmp;
	size_t	i;

	i = *j;
	i = ft_charpos(*s + *j + 1, '\"');
	tmp = ft_strndup(*s + *j + 1, i);
	printf("%p\n", tmp);
	cmd = ft_clearcharset(tmp, "\"");
	*j += i + 2;
	return (cmd);
}

char	*non_special_allocator(char **s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = (*j);
	while ((*s)[(*j)] && !ft_strchr(" \t\n\'\"", (*s)[(*j)]))
		(*j)++;
	cmd = ft_strndup((*s) + i, (*j) - i);
	return (cmd);
}

void	quotes_splitter(char *s, size_t *i, char c)
{
	(*i)++;
	*i += ft_charpos(s + *i + 1, c) + 2;
}
