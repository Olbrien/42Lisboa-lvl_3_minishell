/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:11:09 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/13 15:39:48 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**save_env(char **env)
{
	int		i;
	int		no_envs;
	char	**ret;

	i = 0;
	no_envs = 0;
	while (env[i++])
		no_envs++;
	ret = malloc(sizeof(char *) * (no_envs + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < no_envs)
	{
		ret[i] = ft_strdup(env[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
