/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 17:00:42 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:31 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_complete_quotation(void)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (g_sh.line[i] != '\0')
	{
		if (g_sh.line[i] == '\"' && double_q == 0 && single_q == 0)
			double_q = 1;
		else if (g_sh.line[i] == '\"' && double_q == 1 && single_q == 0)
			double_q = 0;
		else if (g_sh.line[i] == '\'' && single_q == 0 && double_q == 0)
			single_q = 1;
		else if (g_sh.line[i] == '\'' && single_q == 1 && double_q == 0)
			single_q = 0;
		i++;
	}
	if (single_q + double_q == 0)
		return (1);
	else
		return (0);
}

int	cmd_parsing(void)
{
	if (check_complete_quotation() == 0)
	{
		printf("%s\n", "bash: quotation incomplete");
		free_global("line", "empty", "empty", "empty");
		return (0);
	}
	if (process_cmd_tables() == 0)
	{
		free_global("line", "empty", "empty", "empty");
		return (0);
	}
	return (1);
}
