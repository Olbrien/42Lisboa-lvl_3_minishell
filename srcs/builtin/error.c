/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 16:11:28 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 05:49:43 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_error(void)
{
	if (errno == 10)
		printf("%i: command not found\n", 0);
	else if (errno == 2)
		printf("%i: command not found\n", 1);
	else
		printf("%i: command not found\n", g_sh.dollar_error);
	g_sh.dollar_error = 127;
}
