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

char	***alloc_commands(char *str, size_t *nb)
{
	char		***cmd;
	size_t		i;

	i = 0;
	*nb = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(sizeof(char **), (*nb + 1));
	return (cmd);
}

void	quotes_splitter(char *s, size_t *i, char c)
{
	(*i) += (size_t)(ft_strchr(s + *i + 1, c) - (s + *i + 1) + 2);
}
