/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 23:50:52 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:45:09 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	ft_putint(int c)
{
	return (write(1, &c, 1));
}

int	set_capabilities(void)
{
	g_sh.keys_on = tgetstr("ks", &g_sh.buffer);
	if (g_sh.keys_on)
		tputs(g_sh.keys_on, 1, ft_putint);
	g_sh.keys_off = tgetstr("ke", &g_sh.buffer);
	g_sh.up_arrow = tgetstr("ku", &g_sh.buffer);
	g_sh.down_arrow = tgetstr("kd", &g_sh.buffer);
	if (g_sh.islinux == 1)
		g_sh.backspace = tgetstr("kb", &g_sh.buffer);
	else
		g_sh.backspace = ft_strdup("\x7f");
	g_sh.del_line = tgetstr("dl", &g_sh.buffer);
	g_sh.cursor_left = tgetstr("cr", &g_sh.buffer);
	if ((!g_sh.keys_on) || (!g_sh.up_arrow) || (!g_sh.down_arrow)
		|| (!g_sh.backspace) || (!g_sh.del_line) || (!g_sh.keys_off)
		|| (!g_sh.cursor_left))
		return (0);
	else
		return (1);
}

char	*get_termtype(void)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (g_sh.env[i] != NULL)
	{
		if (ft_strncmp(g_sh.env[i], "TERM=", 5) == 0)
		{
			g_sh.env[i] += 5;
			temp = g_sh.env[i];
			g_sh.env[i] -= 5;
			break ;
		}
		i++;
	}
	return (temp);
}

void	init_termcaps(void)
{
	char	*term_type;
	int		ret;

	if (isatty(STDIN_FILENO) != 1)
		exit(EXIT_FAILURE);
	if (tcgetattr(STDIN_FILENO, &g_sh.old_term) == -1)
		exit(EXIT_FAILURE);
	if (g_sh.islinux == 1)
	{
		g_sh.buffer = ft_calloc(2048, 1);
		if (g_sh.buffer == NULL)
			exit(EXIT_FAILURE);
	}
	term_type = get_termtype();
	if (term_type == NULL)
		exit(EXIT_FAILURE);
	ret = tgetent(g_sh.buffer, term_type);
	if (ret <= 0)
		exit(EXIT_FAILURE);
	else if (set_capabilities() == 0)
		exit(EXIT_FAILURE);
}
