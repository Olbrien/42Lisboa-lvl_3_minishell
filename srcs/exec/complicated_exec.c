/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 21:31:30 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:22:32 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	complicated_execute5(t_complicated_exec *norm)
{
	int	status;

	dup2(norm->tmpin, STDIN_FILENO);
	dup2(norm->tmpout, STDOUT_FILENO);
	close(norm->tmpin);
	close(norm->tmpout);
	if (g_sh.pid > 0)
		waitpid(g_sh.pid, &status, 0);
	else if (g_sh.pid < 0)
		printf("ERROR\n");
	if (WIFEXITED(status))
		g_sh.dollar_error = WEXITSTATUS(status);
}

void	complicated_execute4(t_simplecommand **simple_cmd)
{
	char	*bin_path;

	g_sh.pid = fork();
	if (g_sh.pid == 0)
	{
		if ((*simple_cmd)->builtin == 1)
			run_builtin_complicated((*simple_cmd));
		else
		{
			(*simple_cmd) = remove_quotation_marks((*simple_cmd));
			(*simple_cmd) = remove_single_quotation_marks((*simple_cmd));
			if (ft_strchr((*simple_cmd)->command[0], '/'))
				execve((*simple_cmd)->command[0],
					(*simple_cmd)->command, g_sh.env);
			bin_path = get_path((*simple_cmd)->command[0]);
			execve(bin_path, (*simple_cmd)->command, g_sh.env);
			printf("bash: %s: %s\n", (*simple_cmd)->command[0], strerror(errno));
			free(bin_path);
			exit_finale(1);
			exit(127);
		}
		g_sh.dollar_error = 0;
		exit_finale(1);
		exit(0);
	}
}

void	complicated_execute3(t_simplecommand **simple_cmd,
							t_complicated_exec *norm)
{
	if ((*simple_cmd)->next != NULL && (*simple_cmd)->outfile[0] == NULL)
	{
		pipe(norm->fdpipe);
		norm->fdout = norm->fdpipe[1];
		norm->fdin = norm->fdpipe[0];
	}
	dup2(norm->fdout, 1);
	close(norm->fdout);
}

void	complicated_execute2(t_simplecommand **simple_cmd,
							t_complicated_exec *norm)
{
	if (check_outfile((*simple_cmd)) == 1)
		norm->fdout = take_outfile((*simple_cmd));
	else if (check_outfile((*simple_cmd)) == 0)
		norm->fdout = dup(norm->tmpout);
	if (norm->fdout == -1)
	{
		printf("bash: %s: No such file or directory\n",
			(*simple_cmd)->outfile[0]);
	}
}

void	complicated_execute(t_simplecommand *simple_cmd)
{
	t_complicated_exec	norm;

	norm.tmpin = dup(STDIN_FILENO);
	norm.tmpout = dup(STDOUT_FILENO);
	norm.fdin = dup(norm.tmpin);
	while (simple_cmd != NULL)
	{
		complicated_execute2(&simple_cmd, &norm);
		if (infile_stuff(&simple_cmd, &norm) == -1)
			return ;
		if (norm.fdout == -1)
			break ;
		complicated_execute3(&simple_cmd, &norm);
		if (check_builtin_no_fork(&simple_cmd) == 1)
			continue ;
		complicated_execute4(&simple_cmd);
		simple_cmd = simple_cmd->next;
	}
	complicated_execute5(&norm);
}
