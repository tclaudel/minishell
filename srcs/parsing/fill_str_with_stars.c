#include "minishell.h"

char	*fill_str_with_var(char *s, size_t i, size_t j, char *var)
{
	char	*value;

	while (s[i])
	{
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
			if (value)
				s = ft_insert(s, value, i - 1, ft_strlen(var) + 1);
			else
				s = ft_insert(s, " ", i - 1, ft_strlen(var) + 1);
			i += value ? ft_strlen(value) - 1 : 0;
			ft_strdel(&var);
		}
		else
			i++;
	}
	return (s);
}
