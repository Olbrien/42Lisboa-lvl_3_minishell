/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:09:40 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/11 18:46:23 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	only_spaces(char *line)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			a++;
		i++;
	}
	if (a > 0)
		return (0);
	else
		return (1);
}

int	*add_int_to_arr(int *array, int location, int count)
{
	int	a;
	int	i;
	int	*temp;

	i = 0;
	a = 0;
	while (i < count)
		i++;
	temp = malloc(sizeof(int) * (i + 2));
	if (temp == NULL)
		return (NULL);
	while (a < i)
	{
		temp[a] = array[a];
		a++;
	}
	temp[a++] = location;
	temp[a] = '\0';
	free(array);
	return (temp);
}

char	**add_str_to_arrarr(char **array, char *string)
{
	int		a;
	int		i;
	char	**temp;

	i = 0;
	a = 0;
	while (array[i] != NULL)
		i++;
	temp = malloc(sizeof(char *) * (i + 2));
	if (temp == NULL)
		return (NULL);
	while (a < i)
	{
		temp[a] = ft_strdup(array[a]);
		a++;
	}
	temp[a++] = ft_strdup(string);
	temp[a] = NULL;
	free_array(array);
	return (temp);
}

char	*ft_errstr(char c)
{
	char	*ret;

	ret = malloc(2);
	if (!ret)
		return (NULL);
	else
	{
		ret[0] = c;
		ret[1] = 0;
		return (ret);
	}
}
