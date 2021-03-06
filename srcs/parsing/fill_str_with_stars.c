#include "minishell.h"

char	dont_replace_with_quotes(char *s, size_t *i)
{
	if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	return (s[*i] != 0 ? 1 : 0);
}

char	*fill_str_with_var(char *s, size_t i, size_t j, char *var)
{
	char *value;

	while (s[i])
	{
		if (!dont_replace_with_quotes(s, &i))
			break ;
		if (s[i] == '$')
		{
			j = ++i;
			while (s[j] && s[j] != '\"' && s[j] != ' ' && s[j] != '$')
				j++;
			var = ft_substr(s, i, j - i);
			if (var && var[0] == '?')
				value = ft_itoa(sh()->question_mark);
			else
				value = sh()->env->search(sh()->env, var);
			s = ft_insert(s, value ? value : " ", i - 1, ft_strlen(var) + 1);
			i += value ? ft_strlen(value) - 1 : 0;
			ft_strdel(&var);
		}
		else
			i++;
	}
	return (s);
}
