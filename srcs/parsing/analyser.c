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

static int	condition_analyse(char *tok, size_t i, char *start)
{
	if ((ft_strchr("<>&|", tok[i]) &&
	ft_strchr("<&|", tok[i + 1])) || (ft_strchr("<&|", tok[i]) &&
	ft_strchr("<>&|", tok[i + 1])))
		return (ft_return(start, tok, i, i + 1));
	if (tok[i] == '>' && tok[i + 1] == '>' && tok[i + 2] == '>')
		return (ft_return(start, tok, i, 0));
	return (1);
}

int			analyser(char *str, char *tok, size_t i)
{
	char	*cpy;
	char	*start;

	cpy = ft_strdup(str);
	cpy = ft_clearcharset(cpy, " \t", 1);
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
				if (!condition_analyse(tok, i, start))
					return (0);
				i++;
			}
			if (ft_strchr("<>&|", tok[i]))
				return (ft_return(start, tok, i, 0));
		}
	}
	ft_strdel(&start);
	return (1);
}
