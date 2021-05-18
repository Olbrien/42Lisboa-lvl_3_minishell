/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 02:27:42 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 16:27:47 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	has_history(void)
{
	if (g_sh.history_len == 0)
		return (0);
	else
		return (1);
}

void	parse_input_history2(char *buf, int *i, char *input)
{
	tputs(g_sh.cursor_left, 1, ft_putint);
	tputs(g_sh.del_line, 1, ft_putint);
	shell_prompt_line();
	ft_bzero(buf, BUFSIZ);
	ft_strcpy(buf, input);
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

void	parse_input_history(char *buf, int *i)
{
	char	*input;
	int		only_up_arrow;

	only_up_arrow = 0;
	if (g_sh.current_history == g_sh.history_len)
		only_up_arrow = 1;
	if (has_history() == 0)
	{
		ft_bzero(&buf[*i], BUFSIZ - *i);
		return ;
	}
	if (ft_strcmp(g_sh.up_arrow, &buf[*i]) == 0)
	{
		if (g_sh.current_history > 0)
			g_sh.current_history--;
		input = g_sh.history[g_sh.current_history];
		parse_input_history2(buf, i, input);
	}
	else if (ft_strcmp(g_sh.down_arrow, &buf[*i]) == 0 && only_up_arrow == 0)
	{
		if (g_sh.current_history < g_sh.history_len - 1)
			g_sh.current_history++;
		input = g_sh.history[g_sh.current_history];
		parse_input_history2(buf, i, input);
	}
}

void	turn_off_canonical_mode(void)
{
	g_sh.new_term = g_sh.old_term;
	g_sh.new_term.c_lflag &= ~ICANON;
	g_sh.new_term.c_lflag &= ~ECHO;
	g_sh.new_term.c_lflag &= ~ISIG;
	g_sh.new_term.c_cc[VMIN] = 1;
	g_sh.new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_sh.new_term) == -1)
	{
		exit_finale(1);
		exit(errno);
	}
}

void	turn_on_canonical_mode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_sh.old_term) == -1)
	{
		exit_finale (1);
		exit(errno);
	}
}
