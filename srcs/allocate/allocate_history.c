/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_history.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 21:40:49 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:37 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	save_history(void)
{
	int	i;

	i = 0;
	if (g_sh.history == NULL)
	{
		if (g_sh.line != NULL || g_sh.line[0] != '\0')
		{
			g_sh.history = malloc(sizeof(char *) * 2);
			if (g_sh.history == NULL)
				return ;
			g_sh.history[0] = ft_strdup(g_sh.line);
			g_sh.history[1] = NULL;
			g_sh.history_len = 1;
		}
	}
	else
	{
		if (g_sh.line[0] != '\0'
			&& ft_strcmp(g_sh.history[g_sh.history_len - 1],
				g_sh.line) != 0)
		{
			g_sh.history = add_str_to_arrarr(g_sh.history, g_sh.line);
			g_sh.history_len++;
		}
	}
}
