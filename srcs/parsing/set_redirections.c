#include "minishell.h"

void		grep_pipes(char *s, size_t *i, size_t nb)
{
	static size_t	j = 0;

	if (!ft_strncmp(">>", s + (*i), 2))
		sh()->pipes[j] = 'd';
	else
		sh()->pipes[j] = s[(*i)];
	j++;
	sh()->pipes[nb - 1] = 0;
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

size_t		separator_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] && s[i] == '\"')
			quotes_splitter(s, &i, '\"');
		else if (s[i] && s[i] == '\'')
			quotes_splitter(s, &i, '\'');
		else if (s[i] && !ft_strchr(" \t\'\"", s[i])
			&& !ft_strchr(";|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i])
				&& !ft_strchr(";|<>", s[i]))
				i++;
		else if (s[i] && (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i)))
		{
			block++;
			if (!ft_strncmp(">>", s + i, 2))
				i++;
			i++;
		}
	}
	return (block);
}
