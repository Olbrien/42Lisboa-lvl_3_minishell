#include "../../shell.h"

char	*env_isex_elem (char *set)
{
	int		i;
	int		k;
	char	*set_equal;

	set_equal = ft_strjoin(set, "=");
	i = 0;
	k = ft_strlen(set_equal);
	while (g_sh.env[i] != NULL)
	{
		if (!strncmp(set_equal, g_sh.env[i], k))
		{
			free(set_equal);
			return (g_sh.env[i] + k);
		}
		i++;
	}
	ft_strlen(set_equal);
	free(set_equal);
	return ("");
}

int	env_var_update(char *set_tbc, char *new_ct, int is_env)
{
	char	*elem;
	char	*set;

	env_rm_elem(set_tbc);
	set = ft_strjoin(set_tbc, "=");
	if (is_env)
		elem = ft_strjoin(set, env_isex_elem(new_ct));
	else
		elem = ft_strjoin(set, new_ct);
	g_sh.env = add_str_to_arrarr(g_sh.env, elem);
	free(set);
	free(elem);
	return (0);
}

void	init_var_rm_elem (t_env_rm_vars	*va)
{
	va->i = 0;
	va->a = 0;
	va->k = 0;
}

int	env_rm_elem (char *set)
{
	t_env_rm_vars	va;

	init_var_rm_elem(&va);
	va.set_equal = ft_strjoin(set, "=");
	while (g_sh.env[va.i] != NULL)
		va.i++;
	va.temp = malloc(sizeof(char *) * va.i);
	if (va.temp == NULL)
		return (-1);
	while (va.a < (va.i - 1))
	{
		if (ft_strncmp(va.set_equal, g_sh.env[va.k],
				ft_strlen(va.set_equal)))
		{
			va.temp[va.a] = ft_strdup(g_sh.env[va.k]);
			va.a++;
		}
		va.k++;
	}
	va.temp[va.a] = NULL;
	free(va.set_equal);
	free_array(g_sh.env);
	g_sh.env = va.temp;
	return (0);
}

int	env_list_upd_elem (void)
{
	t_linklis	*lst;

	lst = g_sh.ls_start;
	while (lst)
	{
		found_env(&(lst->content));
		lst = lst->next;
	}
	return (0);
}
