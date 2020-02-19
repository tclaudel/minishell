#include "minishell.h"

char		**fill_cmd(char *s, char **cmd, size_t j)
{
	size_t	k;

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
	if (k > 1 && cmd[k - 1])
		cmd[k] = NULL;
	return (cmd);
}

char		**ft_split_cmd(char *s, size_t nb, size_t i, size_t k)
{
	size_t	j;
	char	**entry;

	j = 0;
	entry = (char **)malloc(sizeof(&entry) * (nb + 1));
	sh()->pipes = (char *)ft_calloc(sizeof(char), (nb));
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] && s[i] == '\"')
			quotes_splitter(s, &i, '\"');
		else if (s[i] && s[i] == '\'')
			quotes_splitter(s, &i, '\'');
		else if (s[i] && s[i] && !ft_strchr(" \t\'\"", s[i])
			&& !ft_strchr(";|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i]) &&
				!ft_strchr(";|<>", s[i]))
				i++;
		else if (s[i] && (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i)))
			entry[k++] = found_pipes(s, &j, &i, nb);
	}
	entry[k] = ft_substr(s, j, i);
	entry[k + 1] = NULL;
	return (entry);
}

char		*quote_checker(char *s, size_t quote, size_t dquote)
{
	size_t	i;
	char	*dest;
	char	c;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && !(dquote % 2))
			quote++;
		if (s[i] == '\"' && !(quote % 2))
			dquote++;
		i++;
	}
	if (dquote % 2)
		dest = complete_cmd(s, '\"');
	else if (quote % 2)
		dest = complete_cmd(s, '\'');
	else if (quote % 2 && dquote % 2)
	{
		c = ft_strrchr(s, '\'') < ft_strrchr(s, '\"') ? '\'' : '\"';
		dest = complete_cmd(s, c);
	}
	else
		dest = s;
	return (dest);
}

char		***alloc_commands(char *str, size_t *nb)
{
	char		***cmd;
	size_t		i;

	i = 0;
	*nb = separator_counter(str, 0, 0) + 1;
	cmd = (char ***)ft_calloc(sizeof(char **), (*nb + 1));
	return (cmd);
}

void		parsing(t_sh *sh, char *str)
{
	size_t	i;
	size_t	j;
	size_t	nb;
	char	**entries;

	i = 0;
	j = 0;
	str = quote_checker(str, 0, 0);
	sh->cmd = alloc_commands(str, &nb);
	entries = ft_split_cmd(str, nb, 0, 0);
	while (entries[j])
	{
		sh->cmd[j] = parse(entries[j]);
		ft_display_tab(sh->cmd[j], "cmd");
		j++;
	}
	ft_strdel(&str);
}
