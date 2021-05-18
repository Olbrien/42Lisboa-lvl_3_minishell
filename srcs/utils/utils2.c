/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:46:03 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:25 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	debug_command_table2(t_linklis *ptr)
{
	if (ptr->type == 1)
		printf("Type %d = | \n", ptr->type);
	else if (ptr->type == 2)
		printf("Type %d = >> \n", ptr->type);
	else if (ptr->type == 3)
		printf("Type %d = > \n", ptr->type);
	else if (ptr->type == 4)
		printf("Type %d = < \n", ptr->type);
	else if (ptr->type == 8)
		printf("Type %d = last arg \n", ptr->type);
}

void	debug_command_table(int a)
{
	t_linklis	*ptr;
	int			i;

	i = 0;
	printf("\n------------COMMAND TABLE [%i]------------\n", a);
	printf("\n%s\n", g_sh.cmd_tables[a]);
	ptr = g_sh.ls_start;
	while (ptr)
	{
		printf("\n");
		printf("[ %s]\n", ptr->pre_split);
		debug_command_table2(ptr);
		printf("Builtin: %i\n", ptr->builtin);
		while (ptr->content[i] != NULL)
		{
			printf("arg[%i] = %s\n", i, ptr->content[i]);
			i++;
		}
		printf("arg[%i] = %s\n", i, ptr->content[i]);
		i = 0;
		ptr = ptr->next;
	}
}
