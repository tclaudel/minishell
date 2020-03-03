#include "minishell.h"

void		grep_redir(char *s, size_t *i, size_t nb)
{
	static size_t	j = 0;

	if (!ft_strncmp(">>", s + (*i), 2))
	{
		sh()->redir[j] = 'd';
	}
	else
		sh()->redir[j] = s[(*i)];
	j++;
	sh()->redir[nb - 1] = 0;
	if (j == nb - 1)
		j = 0;
}

char		*found_redir(char *s, size_t *j, size_t *i, size_t nb)
{
	char			*str;

	(void)nb;
	grep_redir(s, i, nb);
	str = ft_strndup(s + (*j), (*i) - (*j));
	dprintf(1, "str\t: %s\n", s + (*i));
	if (!ft_strncmp(">>", s + (*i), 2))
		(*i)++;
	(*i)++;
	dprintf(1, "str\t: %s\n", s + (*i));
	(*j) = (*i);
	return (str);
}
