#include "minishell.h"

size_t		separator_counter(char *s, size_t i, size_t block)
{
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] == '\"')
			i += (size_t)(ft_strchr(s + i + 1, '\"') - (s + i + 1) + 2);
		else if (s[i] == '\'')
			i += (size_t)(ft_strchr(s + i + 1, '\'') - (s + i + 1) + 2);
		else if (s[i] && !ft_strchr(" \t\'\"", s[i])
			&& !ft_strchr(";|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i])
				&& !ft_strchr(";|<>", s[i]))
				i++;
		else if (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i))
		{
			block++;
			if (ft_strchr(";|<>", s[i]))
				i++;
			else if (ft_strcmp(">>", s + i))
				i += 2;
		}
	}
	return (block);
}

char		**fill_cmd(char *s, char **cmd, size_t i, size_t j)
{
	size_t	k;

	k = 0;
	while (s[i])
	{
		i += ft_count_whitespaces(s + i);
		j = i;
		if (s[i] == '\"')
			cmd[k] = double_quote_allocator(s + i, &j);
		else if (s[i] == '\'')
			cmd[k] = simple_quote_allocator(s + i, &j);
		else if (s[i] && !ft_strchr(" \t\n\'\"", s[i]))
		{
			while (s[j] && !ft_strchr(" \t\n\'\"", s[j]))
				j++;
			cmd[k] = ft_strndup(s + i, j - i);
		}
		k++;
		i += j - i;
	}
	return (cmd);
}

char		*found_pipes(char *s, size_t *j, size_t *i, size_t nb)
{
	char	*str;

	(void)nb;
	str = ft_substr(s, *j, *i);
	(*i)++;
	if (ft_strcmp(">>", s + *i))
		(*i)++;
	*j = *i;
	return (str);
}

char		**ft_split_cmd(char *s, size_t nb, size_t i, size_t k)
{
	size_t	j;
	char	**entry;

	j = 0;
	entry = (char **)malloc(sizeof(&entry) * (nb + 1));
	// get_sh_info()->pipes = (char *)malloc(sizeof(char) * (nb));
	while (s[i] && s[i] != '\n')
	{
		i += ft_count_whitespaces(s + i);
		if (s[i] == '\"')
			i += (size_t)(ft_strchr(s + i + 1, '\"') - (s + i + 1) + 2);
		else if (s[i] == '\'')
			i += (size_t)(ft_strchr(s + i + 1, '\'') - (s + i + 1) + 2);
		else if (s[i] && !ft_strchr(" \t\'\"", s[i])
			&& !ft_strchr(";|<>", s[i]))
			while (s[i] && !ft_strchr(" \t\'\"", s[i]) &&
				!ft_strchr(";|<>", s[i]))
				i++;
		else if (ft_strchr(";|<>", s[i]) || ft_strcmp(">>", s + i))
			entry[k++] = found_pipes(s, &j, &i, nb);
	}
	entry[k] = ft_substr(s, j, i);
	entry[k + 1] = NULL;
	return (entry);
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
		j++;
	}
	ft_free_tab(entries);
	ft_strdel(&str);
}
