#include "minishell.h"

char	**fill_cmd(char *s, char **cmd, size_t i, size_t j)
{
	size_t	k;
	char	quotes;

	k = 0;
	while (s[i])
	{
		i += ft_count_whitespaces(s + i);
		j = i;
		if (s[i] == 0)
			break ;
		if (ft_strchr(s + i, '\''))
			quotes = '\'';
		else
			quotes = ' ';
		i += ft_charpos(s + i, '\'') + 1;
		i += ft_charpos(s + i, '\'');
		i += ft_strchr(s + i, ' ') ? ft_charpos(s + i, ' ') : ft_strlen(s + i);
		while (s[i] && s[i] != quotes)
			i++;
		cmd[k++] = ft_clearcharset(ft_substr(s, j, i - j), "\'");
		i += (quotes == '\'');
	}
	cmd[k] = NULL;
	return (cmd);
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
	entry[k] = ft_substr(s, j, i);
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
	if (!(str = handle_dquotes(str)))
	{
		ft_dprintf(2, "minishell: parse error: quotes not completed\n");
		return (0);
	}
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
