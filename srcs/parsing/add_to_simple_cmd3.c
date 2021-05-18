/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_simple_cmd3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:22:41 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:45:10 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_lstnew_simple_add3(t_simplecommand_temp add)
{
	g_sh.simple_cmd->next = malloc(sizeof(t_simplecommand));
	g_sh.simple_cmd = g_sh.simple_cmd->next;
	if (g_sh.simple_cmd == NULL)
		return ;
	if (g_sh.simple_cmd)
	{
		g_sh.simple_cmd->command = add.temp_command;
		g_sh.simple_cmd->infile = new_array_array(add.temp_infile);
		g_sh.simple_cmd->outfile = new_array_array(add.temp_outfile);
		g_sh.simple_cmd->builtin = add.temp_builtin;
		g_sh.simple_cmd->outfiles = add.temp_outfiles;
		g_sh.simple_cmd->infiles = add.temp_infiles;
		g_sh.simple_cmd->append = add.temp_append;
		g_sh.simple_cmd->next = NULL;
	}
}

void	ft_lstnew_simple_add2(t_simplecommand_temp add)
{
	t_simplecommand	*start;
	t_simplecommand	*temp;
	int				i;

	start = g_sh.simple_cmd;
	temp = g_sh.simple_cmd;
	i = 0;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	while (i > 1)
	{
		g_sh.simple_cmd = g_sh.simple_cmd->next;
		i--;
	}
	ft_lstnew_simple_add3(add);
	g_sh.simple_cmd = start;
}

void	ft_lstnew_simple_add1(t_simplecommand_temp add)
{
	g_sh.simple_cmd->command = add.temp_command;
	g_sh.simple_cmd->infile = new_array_array(add.temp_infile);
	g_sh.simple_cmd->outfile = new_array_array(add.temp_outfile);
	g_sh.simple_cmd->builtin = add.temp_builtin;
	g_sh.simple_cmd->outfiles = add.temp_outfiles;
	g_sh.simple_cmd->infiles = add.temp_infiles;
	g_sh.simple_cmd->append = add.temp_append;
	g_sh.simple_cmd->next = NULL;
}

void	ft_lstnew_simple_add(t_simplecommand_temp add)
{
	if (g_sh.simple_cmd == NULL)
	{
		g_sh.simple_cmd = malloc(sizeof(t_simplecommand));
		if (g_sh.simple_cmd == NULL)
			return ;
		if (g_sh.simple_cmd)
			ft_lstnew_simple_add1(add);
	}
	else
		ft_lstnew_simple_add2(add);
}
