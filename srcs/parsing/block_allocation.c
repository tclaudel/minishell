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
	size_t		j;
	size_t		k;
	static int	a = 0;

	a++;
	j = ft_charpos(s + *i + 1, c) + 2;
	k = ft_charpos(s + *i + 1, ' ') + 2;
	if (a == 1)
		ft_printf("j\t: %u\nk\t: %u\n", i, j);
	(*i) += j;
	if (a > 2)
		a = 0;
}
