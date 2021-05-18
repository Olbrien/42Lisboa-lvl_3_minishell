/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 12:38:52 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 14:04:30 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	shell_prompt3(char *buf, int i)
{
	buf[i - 1] = '\0';
	g_sh.line = ft_strdup(buf);
	if (only_spaces(g_sh.line) == 1)
		free_global("line", "empty", "empty", "empty");
	if (g_sh.line == NULL || g_sh.line[0] == '\0')
		shell_prompt();
}

int	shell_prompt2(int norm, char **buf)
{
	if (norm == 0)
	{
		turn_on_canonical_mode();
		write (1, "exit\n", 6);
		exit_finale(0);
		exit(0);
	}
	else if (norm == 1)
	{
		printf("^C\n");
		g_sh.dollar_error = 130;
		shell_prompt_line();
		ft_bzero(buf, BUFSIZ);
		return (0);
	}
	else if (norm == 2)
	{
		g_sh.current_history = g_sh.history_len;
		g_sh.line = NULL;
		shell_prompt_line();
	}
	return (0);
}

void	shell_prompt(void)
{
	char				buf[BUFSIZ];
	t_norminette_struct	norm;

	norm.i = 0;
	ft_bzero(buf, BUFSIZ);
	shell_prompt2(2, (void *)&buf);
	while (!ft_strchr(buf, '\n'))
	{
		norm.nb_char_read = read(STDIN_FILENO, &buf[norm.i], BUFSIZ - norm.i);
		if (*buf == 4)
			shell_prompt2(0, (void *)&buf);
		else if (buf[norm.i] == 3)
			norm.i = shell_prompt2(1, (void *)&buf);
		else if (buf[norm.i] == 28 || buf[norm.i] == 4 || buf[norm.i] == 26)
			buf[norm.i] = 0;
		else if (is_up_down_arrow(&buf[norm.i]))
			parse_input_history(buf, &norm.i);
		else if (ft_strcmp(&buf[norm.i], g_sh.backspace) == 0)
			delete_single_char(buf, &norm.i);
		else if (norm.nb_char_read > 1)
			ft_bzero(&buf[norm.i], BUFSIZ - norm.i);
		else
			norm.i += write(STDOUT_FILENO, &buf[norm.i], 1);
	}
	shell_prompt3(buf, norm.i);
}
