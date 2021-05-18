/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 19:48:47 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/13 15:41:06 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_exit(char **content)
{
	int	a;
	int	i;

	a = 255;
	i = 0;
	while (content[i] != NULL)
		i++;
	i = i - 1;
	if (i == 0)
	{
		exit_finale(1);
		exit (0);
	}
	else if (i == 1)
	{
		a = ft_atoi(content[1]);
		exit_finale(1);
		exit (a);
	}
}
