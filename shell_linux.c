/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_linux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:57:53 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/18 18:46:25 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	loop_command_tables(void)
{
	int	i;

	i = 0;
	while (g_sh.cmd_tables[i] != NULL)
	{
		if (add_to_list(i) == 0)
			break ;
		if (g_sh.isdebugger == 1)
			debug_command_table(i);
		add_to_simple_commands_list();
		if (g_sh.isdebugger == 2)
			debug_simple_commands();
		exec_command();
		ft_linklstclear(&g_sh.ls_start);
		ft_lstclear_simple_struct(&g_sh.simple_cmd);
		i++;
	}
	free_global("cmd_tables", "line", "empty", "empty");
}

void	shell_prompt_line(void)
{
	char	buf[1001];
	char	*path;

	path = getcwd(buf, 1000);
	if (g_sh.absolute_path == 0)
		write(1, "\x1b[90mminishell\x1b[91m$ ", 22);
	else
	{
		write(1, "\x1b[90m", 6);
		write(1, path, ft_strlen(path));
		write(1, "\x1b[91m$ ", 8);
	}
}

void	shell_loop(void)
{
	while (g_sh.status == 1)
	{
		turn_off_canonical_mode();
		shell_prompt();
		save_history();
		turn_on_canonical_mode();
		if (cmd_parsing() == 0)
			continue ;
		loop_command_tables();
	}
}

int	main (int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	g_sh.absolute_path = 0;
	g_sh.testing = 0;
	g_sh.env = save_env(env);
	g_sh.pid = 0;
	g_sh.status = 1;
	g_sh.islinux = 1;
	g_sh.isdebugger = 0;
	g_sh.dollar_error = errno;
	signal(SIGQUIT, &sig_quit);
	signal(SIGINT, &sig_int);
	init_termcaps();
	shell_loop();
	return (0);
}
