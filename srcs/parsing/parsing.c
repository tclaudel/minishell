#include "minishell.h"


char			**fill_cmd(char *s, size_t nb, char **cmd, size_t i)
{
	size_t	j;
	size_t	k;

	j = 0;
	k = 0;
	while (s[i] && k < nb)
	{
		if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
		}
		dprintf(1, "ret\t: %zu\n", ft_count_whitespaces(s + i));
		j = i;
		if (s[i] == '\"' || s[i] == '\'')
		{
			j += (size_t)(ft_strchr(s + i + 1, '\"') - (s + i + 1) + 2);
			cmd[k] = ft_strndup(s + i, j - i);
		}
		else if (s[i] == '\'')
		{
			j += (size_t)(ft_strchr(s + i + 1, '\'') - (s + i + 1) + 2);
			cmd[k] = ft_strndup(s + i, j - i);
		}
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
