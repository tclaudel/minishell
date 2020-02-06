#include "minishell.h"


static void		sort_cpy(t_strhash *cpy)
{
	t_strhash	tmp;
	size_t		i;

	i = 0;
	while (cpy[i + 1].key)
	{
		if (ft_strcmp(cpy[i].key, cpy[i + 1].key) > 0)
		{
			tmp = cpy[i];
			cpy[i] = cpy[i + 1];
			cpy[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

static void		builtin_export_empty(t_sh *sh)
{
	t_strhash *cpy;
	size_t i;

	i = 0;
	while (sh->env[i].key)
		i++;
	cpy = malloc(sizeof(t_strhash) * (i + 1));
	i = 0;
	while (sh->env[i].key)
	{
		cpy[i] = sh->env[i];
		i++;
	}
	cpy[i].key = NULL;
	cpy[i].value = NULL;
	sort_cpy(cpy);
	i = -1;
	while (cpy[++i].key)
	{
		ft_dprintf(1, "declare -x ");
		ft_dprintf(1, "%s", cpy[i].key);
		ft_dprintf(1, "%s", "=");
		ft_dprintf(1, "%s\n", cpy[i].value);
	}
	free(cpy);
}

static void		add_key(t_sh *sh, char **key, size_t i, size_t j)
{
	char	**splited;
	size_t	k;

	while (key[++j])
	{
		splited = ft_split(key[j], '=');
		ft_display_tab(splited, "split");
		if (splited[0] && ft_get_hash_value(sh->env, splited[0]))
		{
			change_value(sh->env, splited[0], splited[1]);
			ft_free_tab(splited);
			continue ;
		}
		k = 0;
		while (key[j][k] && key[j][k] != '=')
			k++;
		if (key[j][k] != '=')
		{
			ft_free_tab(splited);
			continue ;
		}
		sh->env[i].key = ft_strndup(key[j], k);
		sh->env[i++].value = ft_strdup(key[j] + k + 1);
		ft_free_tab(splited);
	}
}

void		builtin_export(t_sh *sh, char **key)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!key[1])
		builtin_export_empty(sh);
	while (sh->env[i].key)
		i++;
	j = ft_tablen(key);
	sh->env = realloc_hash(sh->env, sizeof(t_strhash) * (i + j));
	add_key(sh, key, i, 0);
	sh->question_mark = 0;
}