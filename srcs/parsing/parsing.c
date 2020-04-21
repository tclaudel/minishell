#include "minishell.h"

void	quotes_splitter(char *s, size_t *i, char c)
{
	(*i)++;
	*i += ft_charpos(s + *i + 1, c) + 2;
}

char	**ft_split_cmd(char *s, size_t nb, size_t i, size_t k)
{
	size_t		j;
	char		**entry;

	j = 0;
	entry = (char **)malloc(sizeof(&entry) * (nb + 1));
	sh()->redir = (char *)ft_calloc(sizeof(char), (nb + 1));
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] && s[i] == '\"')
			quotes_splitter(s, &i, '\"');
		else if (s[i] && s[i] == '\'')
			quotes_splitter(s, &i, '\'');
		else if (s[i] && s[i] && !ft_strchr(" \t\'\"", s[i]) &&
			!ft_strchr(";|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i]) &&
					!ft_strchr(";|<>", s[i]))
				i++;
		else if (s[i] && (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i)))
			entry[k++] = found_redir(s, &j, &i, nb);
	}
	j += ft_count_whitespaces(s + j);
	entry[k] = ft_substr(s, j, i - j);
	entry[k + 1] = NULL;
	return (entry);
}

char	***alloc_commands(char *str, size_t *nb)
{
	char	***cmd;

	*nb = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(sizeof(char **), (*nb + 1));
	return (cmd);
}

char	parsing(char *str)
{
	size_t	j;
	size_t	nb;
	char	**entries;

	j = 0;
	str = fill_str_with_var(str, 0, 0, NULL);
	if (quotes_error(str))
		return (0);
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		str = join_quotes(str, 0, 0);
	sh()->cmd = alloc_commands(str, &nb);
	entries = ft_split_cmd(str, nb, 0, 0);
	while (entries[j])
	{
		sh()->cmd[j] = parse(entries[j]);
		j++;
	}
	ft_strdel(&str);
	free(entries);
	return (1);
}
