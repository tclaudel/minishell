#include "minishell.h"

static char	*ft_strsep(char **stringp, const char *delim)
{
	char	*begin;
	char	*end;

	begin = *stringp;
	if (begin == NULL)
		return (NULL);
	end = begin + ft_strcspn(begin, delim);
	if (*end)
	{
		*end++ = '\0';
		*stringp = end;
	}
	else
		*stringp = NULL;
	return (begin);
}

static int	ft_return(char *cpy, char *tok, size_t i, size_t j)
{
	if (j == 0)
	{
		ft_dprintf(2, "minishell: parse error near `%c'\n",
		tok[i]);
	}
	else
	{
		ft_dprintf(2, "minishell: parse error near `%c%c'\n",
		tok[i], tok[j]);
	}
	ft_strdel(&cpy);
	return (0);
}

char		*handle_dquotes(char *str)
{
	size_t	i;
	short	quotes;
	short	dquotes;

	i = 0;
	quotes = 0;
	dquotes = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quotes++;
		if (str[i] == '\"')
			dquotes++;
		i++;
	}
	if (quotes % 2 != 0)
		return (NULL);
	if (dquotes % 2 != 0)
		return (NULL);
	return (str);
}

int			analyser(char *str, char *tok, char *cpy)
{
	char	*start;
	size_t	i;

	cpy = ft_strdup(str);
	cpy = ft_clearcharset(cpy, " \t");
	start = cpy;
	while ((tok = ft_strsep(&cpy, ";")))
	{
		if (tok[0])
		{
			i = 0;
			if (ft_strchr("<>&|", tok[i]))
				return (ft_return(start, tok, i, 0));
			while (tok[i + 1])
			{
				if ((ft_strchr("<>&|", token[i]) && ft_strchr("<&|", token[i + 1])) ||
				(ft_strchr("<&|", token[i]) && ft_strchr("<>&|", token[i + 1])))
					return (ft_return(start, token, i, i + 1));
				i++;
			}
			if (ft_strchr("<>&|", tok[i]))
				return (ft_return(start, tok, i, 0));
		}
	}
	ft_strdel(&start);
	return (1);
}
