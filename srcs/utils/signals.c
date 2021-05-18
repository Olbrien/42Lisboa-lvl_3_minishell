/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:15:02 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 06:38:01 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	sig_int(int signo)
{
	(void)signo;
	printf("\n");
	g_sh.dollar_error = 130;
}

void	sig_quit(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit (core dumped)\n", STDERR);
	g_sh.dollar_error = 131;
	kill(g_sh.pid, SIGQUIT);
}
