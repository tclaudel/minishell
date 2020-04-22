#include "minishell.h"

static char		next_quotes(char *s, size_t i)
{
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (s[i]);
		i++;
	}
	return (0);
}

int				print_quotes_error(void)
{
	ft_dprintf(2, "minishell: parse error: quotes not completed\n");
	return (EXIT_FAILURE);
}

int				quotes_error(char *s)
{
	size_t	i;
	char	quotes;

	i = 0;
	if (!ft_strchr(s, '\'') && !ft_strchr(s, '\"'))
		return (EXIT_SUCCESS);
	quotes = '\"';
	if (ft_strchr(s, '\'') &&
		((ft_strchr(s, '\'') < ft_strchr(s, '\"') || !ft_strchr(s, '\"'))))
		quotes = '\'';
	i += ft_charpos(s, quotes) + 1;
	if (!s[i])
		return (print_quotes_error());
	while (s[i])
	{
		if (ft_strchr(s + i, quotes))
			i += ft_charpos(s + i, quotes) + 1;
		else
			return (print_quotes_error());
		if (!s[i])
			break ;
		quotes = next_quotes(s, i);
		i += ft_charpos(s + i, quotes) + 1;
	}
	return (EXIT_SUCCESS);
}
