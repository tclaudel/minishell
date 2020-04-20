#include "minishell.h"

char			*complete_cmd(char *s, char c)
{
	char		*str;
	char		buff[1024];
	int			ret;

	str = ft_strdup("\n");
	ft_printf(""YELLOW_BOLD"> "RESET"");
	while (1)
	{
		ret = read(0, buff, 1023);
		buff[ret] = 0;
		str = ft_strfjoin(str, buff, 1);
		if (ft_strchr(str, c))
			break ;
		if (buff[0] != 0)
			ft_printf(""YELLOW_BOLD"> "RESET"");
	}
	s = ft_strfjoin(s, str, 3);
	return (s);
}

size_t			bloc_counter(char *s, size_t i, size_t block)
{
	char	quotes;

	while (s[i])
	{
		i += ft_count_whitespaces(s + i);
		if (ft_strchr(s + i, '\'') || ft_strchr(s + i, '\"'))
		{
			quotes = s[i++];
			if (quotes != '\'' && quotes != '\"')
				quotes = ' ';
			while (s[i] && s[i] != quotes)
				i++;
			block++;
		}
		else
		{
			while (s[i] && s[i] != ' ')
				i++;
			block++;
			break ;
		}
	}
	return (block);
}

char			**parse(char *s)
{
	size_t		nb;
	char		**cmd;

	nb = bloc_counter(s, 0, 0);
	cmd = (char **)malloc(sizeof(char *) * (nb + 2));
	cmd[nb] = NULL;
	cmd = fill_cmd(s, cmd, 0, 0);
	return (cmd);
}
