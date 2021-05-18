/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 03:21:50 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:31 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	last_elem_lis(t_var_add_tlis *va, int index)
{
	va->type = 8;
	va->aux = ft_substr(g_sh.cmd_tables[index],
			va->start, (va->i + 1) - va->start);
	ft_linkadd_back(&g_sh.ls_start, ft_linknew(va->aux, va->type));
}

int	sep_link(int index, int *a, int *type)
{
	t_var_seplink	va;

	va.i = *a;
	va.s = 0;
	va.single_q = 0;
	va.double_q = 0;
	va.n = g_sh.cmd_tables[index][va.i];
	while (va.n != '\0')
	{
		if (sep_link_2(&va, a, index, type) == va.i)
			return (va.i);
		va.n = g_sh.cmd_tables[index][va.i];
	}
	if (va.double_q || va.single_q)
		g_sh.error = 1;
	return (0);
}
