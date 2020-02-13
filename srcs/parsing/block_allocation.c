#include "minishell.h"

char	*double_quote_allocator(char *s, size_t *j)
{
	char	*cmd;
	char	*tmp;
	size_t	i;

	i = *j;
	i = ft_charrpos(s + *j + 1, '\"');
	tmp = ft_strndup(s + *j + 1, i);
	cmd = ft_clearcharset(s + *j + 1, "\"");
	*j += i + 2;
	return (cmd);
}

char	*simple_quote_allocator(char *s, size_t *j)
{
	char	*cmd;
	size_t	i;

	i = *j;
	i = ft_charrpos(s + *j + 1, '\'');
	cmd = ft_strndup(s + *j + 1, i);
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
	size_t		j;
	size_t		k;

	j = ft_charpos(s + *i + 1, c);
	k = ft_charpos(s + *i + 1, ' ');
	(*i) += j + 2;
	if (k == 0)
		(*i) += ft_charrpos(s + *i + 1, c);
}
