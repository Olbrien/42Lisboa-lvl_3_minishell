/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 03:32:21 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:28 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_testing(void)
{
	if (g_sh.testing == 1)
	{
		printf("testing: OFF\n");
		g_sh.testing = 0;
	}
	else
	{
		printf("testing: ON\n");
		g_sh.testing = 1;
	}
}
