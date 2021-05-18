#include "../../shell.h"

int	quotes_check_1(char t, int *single_q, int *double_q)
{
	if (t == '\"' && *double_q == 0 && *single_q == 0 )
		*double_q = 1;
	else if (t == '\"' && *double_q == 1 && *single_q == 0 )
		*double_q = 0;
	else if (t == '\'' && *single_q == 0 && *double_q == 0)
		*single_q = 1;
	else if (t == '\'' && *single_q == 1 && *double_q == 0 )
		*single_q = 0;
	if (*double_q == 0 && *single_q == 0)
		return (1);
	else
		return (0);
}

void	found_env5(t_fou_env_var *var)
{
	ft_strlcpy(var->temp + var->l, env_isex_elem(var->search),
		ft_strlen(env_isex_elem(var->search) - 1));
	var->l += ft_strlen(env_isex_elem(var->search));
}

void	found_env6(t_fou_env_var *var)
{
	while (!ft_strchr(DELIMITERS3, var->ret[var->i][var->k + 1])
		&& var->ret[var->i][var->k + 1])
	{
		if (var->ret[var->i][var->k + 1] == '\"')
			break ;
		var->k++;
	}
}
