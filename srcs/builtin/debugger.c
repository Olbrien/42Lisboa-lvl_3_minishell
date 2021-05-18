/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 03:52:56 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:55:37 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_debugger(void)
{
	if (g_sh.isdebugger == 0)
	{
		printf("debugger 1\n");
		g_sh.isdebugger = 1;
	}
	else if (g_sh.isdebugger == 1)
	{
		printf("debugger 2\n");
		g_sh.isdebugger = 2;
	}
	else if (g_sh.isdebugger == 2)
	{
		printf("debugger 0\n");
		g_sh.isdebugger = 0;
	}
}
