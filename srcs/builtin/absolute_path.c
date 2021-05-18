/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 02:53:37 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:27 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_absolute_path(void)
{
	if (g_sh.absolute_path == 1)
		g_sh.absolute_path = 0;
	else
		g_sh.absolute_path = 1;
}
