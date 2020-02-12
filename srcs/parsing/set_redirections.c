#include "minishell.h"

void		grep_pipes(char *s, size_t *i, size_t nb)
{
	static size_t	j = 0;

	if (!ft_strncmp(">>", s + (*i), 2))
		get_sh_info()->pipes[j] = 'd';
	else
		get_sh_info()->pipes[j] = s[(*i)];
	j++;
	get_sh_info()->pipes[nb - 1] = 0;
	if (j == nb - 1)
		j = 0;
}

char		*found_pipes(char *s, size_t *j, size_t *i, size_t nb)
{
	char			*str;

	(void)nb;
	grep_pipes(s, i, nb);
	str = ft_strndup(s + (*j), (*i) - (*j));
	if (ft_strcmp(">>", s + (*i)))
		(*i)++;
	(*j) = (*i);
	return (str);
}
