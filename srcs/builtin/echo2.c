/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 03:19:43 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:19:24 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_putnstr2(t_splvariab	*varia, char *str, int n, int i)
{
	while (str[++i] && i < (int)ft_strlen(str) + n)
	{
		if (varia->its_clos)
			varia->its_clos = its_open_quo(varia, str[i + 1]);
		else
			varia->its_clos = its_open_quo(varia, str[i]);
		if (str[i] == '$' && str[i + 1] == '?' && varia->double_q)
		{
			ft_putnbr_fd(g_sh.dollar_error, 1);
			i++;
		}
		else if (str[i] == '\\' && str[i + 1] == 'n')
			func_case(n, &i);
		else if (!ft_strchr(OPEN_QUOTE_EC, str[i]) || !varia->its_clos)
			write(1, &str[i], 1);
	}
}

int	func_case(int n, int *i)
{
	if (n < 1)
		write(1, "\n", 1);
	else
		write(1, "n", 1);
	*i += 1;
	return (0);
}
