#include "minishell.h"

static char	ft_isspace(int c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	return (0);
}

int			analyser(char *buf)
{
	size_t	i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '|')
	{
		ft_dprintf(2, "minishell: parse error \
		near `%c%c'\n", buf[i], buf[i + 1]);
		return (0);
	}
	while (buf[i])
	{
		if (buf[i] == ';' && (buf[i + 1] == ';' || buf[i + 1] == '|'))
		{
			ft_dprintf(2, "minishell: parse \
			error near `%c%c'\n", buf[i], buf[i + 1]);
			return (0);
		}
		i++;
	}
	return (1);
}