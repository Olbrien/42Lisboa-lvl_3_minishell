/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_exec3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:26:20 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 23:39:56 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_builtin_no_fork3(t_simplecommand **lista, int i)
{
	if (ft_strcmp((*lista)->command[0], "debugger") == 0)
	{
		ft_debugger();
		(*lista) = (*lista)->next;
		i = 1;
	}
	return (i);
}

int	check_builtin_no_fork2(t_simplecommand **lista)
{
	int	i;

	i = 0;
	if (ft_strcmp((*lista)->command[0], "export") == 0)
	{
		ft_export((*lista)->command);
		(*lista) = (*lista)->next;
		i = 1;
	}
	else if (ft_strcmp((*lista)->command[0], "unset") == 0)
	{
		ft_unset((*lista)->command);
		(*lista) = (*lista)->next;
		i = 1;
	}
	else if (ft_strcmp((*lista)->command[0], "$?") == 0)
	{
		errno = 0;
		ft_error();
		(*lista) = (*lista)->next;
		i = 1;
	}
	if (i == 0)
		i = check_builtin_no_fork3(lista, i);
	return (i);
}

int	check_builtin_no_fork(t_simplecommand **lista)
{
	int	i;

	i = 0;
	if (ft_strcmp((*lista)->command[0], "cd") == 0)
	{
		ft_cd((*lista)->command);
		(*lista) = (*lista)->next;
		return (1);
	}
	else if (ft_strcmp((*lista)->command[0], "env") == 0)
	{
		ft_env();
		(*lista) = (*lista)->next;
		return (1);
	}
	else if (ft_strcmp((*lista)->command[0], "exit") == 0)
	{
		ft_exit((*lista)->command);
		(*lista) = (*lista)->next;
		return (1);
	}
	if (i == 0)
		i = check_builtin_no_fork2(lista);
	return (i);
}

void	run_builtin_complicated(t_simplecommand *lista)
{
	if (ft_strcmp(lista->command[0], "echo") == 0)
		ft_echo(lista->command);
	else if (ft_strcmp(lista->command[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(lista->command[0], "history") == 0)
		ft_history();
}
