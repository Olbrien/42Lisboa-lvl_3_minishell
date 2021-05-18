/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:43:44 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:42:55 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	free_global2(char *f1, char *f2, char *f3, char *f4)
{
	if (!ft_strcmp(f1, "env") || !ft_strcmp(f2, "env")
		|| !ft_strcmp(f3, "env") || !ft_strcmp(f4, "env"))
	{
		free_array(g_sh.env);
		g_sh.env = NULL;
	}
	if (!ft_strcmp(f1, "args") || !ft_strcmp(f2, "args")
		|| !ft_strcmp(f3, "args") || !ft_strcmp(f4, "args"))
	{
		free_array(g_sh.args);
		g_sh.args = NULL;
	}
}

void	free_global(char *f1, char *f2, char *f3, char *f4)
{
	if (!ft_strcmp(f1, "line") || !ft_strcmp(f2, "line")
		|| !ft_strcmp(f3, "line") || !ft_strcmp(f4, "line"))
	{
		free(g_sh.line);
		g_sh.line = NULL;
	}
	if (!ft_strcmp(f1, "history") || !ft_strcmp(f2, "history")
		|| !ft_strcmp(f3, "history") || !ft_strcmp(f4, "history"))
	{
		free_array(g_sh.history);
		g_sh.history = NULL;
	}
	if (!ft_strcmp(f1, "cmd_tables") || !ft_strcmp(f2, "cmd_tables")
		|| !ft_strcmp(f3, "cmd_tables") || !ft_strcmp(f4, "cmd_tables"))
	{
		free_array(g_sh.cmd_tables);
		g_sh.cmd_tables = NULL;
	}
	free_global2(f1, f2, f3, f4);
}

void	exit_finale(int free_list)
{
	free_array(g_sh.env);
	free(g_sh.line);
	if (g_sh.history_len > 0)
		free_array(g_sh.history);
	if (g_sh.cmd_tables != NULL)
		free_array(g_sh.cmd_tables);
	if (free_list == 1)
		ft_linklstclear(&g_sh.ls_start);
	if (g_sh.simple_cmd != NULL)
		ft_lstclear_simple_struct(&g_sh.simple_cmd);
	if (g_sh.islinux == 0)
		free(g_sh.backspace);
}
