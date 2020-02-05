#include "minishell.h"

char			**fill_cmd(char *s, char **cmd, size_t i, size_t j)
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

void			parsing(t_sh *sh, char *str)
{
	size_t	i;
	size_t	j;
	char	**entries;

	i = 0;
	j = 0;
	str = quote_checker(str);
	sh->cmd = alloc_commands(str, ';');
	entries = ft_split(str, ';');
	while (entries[j])
	{
		sh->cmd[j] = parse(entries[j]);
		j++;
	}
	ft_free_tab(entries);
	ft_strdel(&str);
}
