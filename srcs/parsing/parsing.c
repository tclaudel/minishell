#include "minishell.h"

char **fill_cmd(char *s, char **cmd, size_t j)
{
	size_t k;

	k = 0;
	while (s[j])
	{
		j += ft_count_whitespaces(s + j);
		if (s[j] == '\"')
			cmd[k] = double_quote_allocator(&s, &j);
		else if (s[j] == '\'')
			cmd[k] = simple_quote_allocator(s, &j);
		else if (s[j] && !ft_strchr(" \t\n\'\"", s[j]))
			cmd[k] = non_special_allocator(&s, &j);
		k++;
	}
	ft_strdel(&s);
	return (cmd);
}

char **ft_split_cmd(char *s, size_t nb, size_t i, size_t k)
{
	size_t j;
	char **entry;

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
		else if (s[i] && s[i] && !ft_strchr(" \t\'\"", s[i]) && !ft_strchr(";|<>", s[i]))
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

char *join_quotes(char *s, size_t i, size_t j, char c)
{
	char	*dest;
	char	closed;

	closed = 0;
	dest = (char *)ft_calloc(sizeof(char *), ft_strlen(s) + 1);
	while (s[i])
	{
		while (s[i] && s[i] != '\'' && s[i] != '\"')
			dest[j++] = s[i++];
		if (!s[i])
			break;
		c = s[i];
		dest[j++] = '\'';
		i++;
		while (s[i] && s[i] != c && s[i] != ' ')
		{
			dest[j++] = s[i++];
			closed = s[i];
		}
		if (s[i] && s[i + 1] && (s[i + 1] == '\'' || s[i + 1] == '\"'))
			i += 2;
		else if (s[i])
			i++;
		if (closed == '\'' || closed == '\"')
			ft_strrchr(dest, '\'')[0] = ' ';
	}
	ft_strdel(&s);
	return (dest);
}

char ***alloc_commands(char *str, size_t *nb)
{
	char ***cmd;

	*nb = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(sizeof(char **), (*nb + 1));
	return (cmd);
}

char parsing(char *str)
{
	size_t j;
	size_t nb;
	char **entries;

	j = 0;
	str = fill_str_with_var(str, 0, 0, NULL);
	if (!(str = handle_dquotes(str)))
	{
		ft_dprintf(2, "minishell: parse error: quotes not completed\n");
		return (0);
	}
	if (ft_strchr(str, '\'') || ft_strchr(str, '\"'))
		str = join_quotes(str, 0, 0, 0);
	// dprintf(1, "str\t: %s\n", str);
	sh()->cmd = alloc_commands(str, &nb);
	entries = ft_split_cmd(str, nb, 0, 0);
	while (entries[j])
	{
		sh()->cmd[j] = parse(entries[j]);
		// ft_display_tab(sh()->cmd[j], "cmd");
		j++;
	}
	ft_strdel(&str);
	free(entries);
	return (1);
}
