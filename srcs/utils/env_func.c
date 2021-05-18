#include "../../shell.h"

void	found_env4(t_fou_env_var *var)
{
	if (var->ret[var->i][var->k] == '$' && var->ret[var->i][var->k + 1]
		&& !ft_strchr(SHELL_DELIMITERS, var->ret[var->i][var->k + 1])
		&& var->ret[var->i][var->k + 1] != '?')
	{
		var->old_index = var->k;
		found_env6(var);
		var->search = ft_substr(var->ret[var->i], var->old_index + 1,
				var->k - var->old_index);
		if (ft_strlen(env_isex_elem(var->search)))
			found_env5(var);
		free(var->search);
	}
	else
	{
		var->temp[var->l] = var->ret[var->i][var->k];
		var->l++;
	}
	var->k++;
}

void	found_env3(t_fou_env_var *var)
{
	var->temp[var->l] = '\0';
	if (var->l == 0)
	{
		free(var->ret[var->i]);
		var->ret[var->i] = ft_strdup("");
	}
	if (var->l > 0)
	{
		free(var->ret[var->i]);
		var->ret[var->i] = ft_strdup(var->temp);
	}
}

void	found_env2(t_fou_env_var *var)
{
	while (var->ret[++var->i])
	{
		if (var->ret [var->i][0] == '\'')
			continue ;
		var->k = 0;
		var->l = 0;
		while (var->ret[var->i][var->k])
			found_env4(var);
		found_env3(var);
	}
}

void	found_env(char ***original)
{
	t_fou_env_var	var;

	var.i = -1;
	var.ret = *original;
	if (!(var.ret))
		return ;
	found_env2(&var);
}

int	env_add_elem (char *set, char *content)
{
	char	*new_elem;

	new_elem = ft_strjoin(set, content);
	add_str_to_arrarr(g_sh.env, new_elem);
	return (0);
}
