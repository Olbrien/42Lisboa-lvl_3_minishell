/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:12:50 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:19:12 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	its_open_quo(t_splvariab *varia, char t)
{
	if (t == '\"' && varia->double_q == 0 && varia->single_q == 0 )
		varia->double_q = 1;
	else if (t == '\"' && varia->double_q == 1 && varia->single_q == 0 )
		varia->double_q = 0;
	else if (t == '\'' && varia->single_q == 0 && varia->double_q == 0)
		varia->single_q = 1;
	else if (t == '\'' && varia->single_q == 1 && varia->double_q == 0 )
		varia->single_q = 0;
	if (varia->double_q == 0 && varia->single_q == 0)
		return (1);
	else
		return (0);
}

void	var_putnstr_a_init(t_splvariab	*varia, int *i)
{
	*i = -1;
	varia->its_clos = 1;
	varia->double_q = 0;
	varia->single_q = 0;
}

void	ft_putnstr(char *str, int n)
{
	int			i;
	t_splvariab	varia;

	var_putnstr_a_init(&varia, &i);
	if (n < 0)
		ft_putnstr2(&varia, str, n, i);
	else
	{
		while (str[++i] && i < n)
		{
			if (varia.its_clos)
				varia.its_clos = its_open_quo(&varia, str[i + 1]);
			else
				varia.its_clos = its_open_quo(&varia, str[i]);
			if (str[i] == '$' && str[i + 1] == '?')
			{
				ft_putnbr_fd(g_sh.dollar_error, 1);
				i++;
			}
			else if (str[i] == '\\' && str[i + 1] == 'n')
				func_case(n, &i);
			else if (!ft_strchr(OPEN_QUOTE_EC, str[i]) || !varia.its_clos)
				write(1, &str[i], 1);
		}
	}
}

static void	echo_out(char **str, int pos)
{
	int		quote;

	quote = (str[pos][0] == '"' || str[pos][0] == '\'');
	if (quote)
		ft_putnstr(str[pos] + 1, -1);
	else
		ft_putnstr(str[pos], ft_strlen(str[pos]));
	if (str[pos + 1])
		write(1, " ", 1);
}

int	ft_echo(char **content)
{
	int		i;
	int		n_flag;

	n_flag = 0;
	if (!content[1])
	{
		write(1, "\n", 1);
		return (1);
	}
	else if (!ft_strcmp(content[1], "-n"))
		n_flag = 1;
	i = 0;
	if (n_flag)
		++i;
	while (content[++i])
	{
		if (ft_strlen(content[i]))
			echo_out(content, i);
		if (!content[i + 1] && !n_flag)
			write(1, "\n", 1);
	}
	return (1);
}
