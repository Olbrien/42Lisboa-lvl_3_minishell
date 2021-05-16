/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:27:55 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:17 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_sh.env[i])
	{
		printf("%s\n", g_sh.env[i++]);
	}
}
