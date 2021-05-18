/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 16:51:03 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:23 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	exec_command(void)
{
	t_linklis		*list;
	t_simplecommand	*simple_cmd;

	simple_cmd = g_sh.simple_cmd;
	list = g_sh.ls_start;
	if (list->content[0] == NULL)
	{
		printf(" : command not found.\n");
		return ;
	}
	complicated_execute(simple_cmd);
}
