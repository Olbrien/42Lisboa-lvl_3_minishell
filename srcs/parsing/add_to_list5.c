/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:40:05 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:27 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	count_elems1(char **original)
{
	int	i;
	int	elems;

	elems = 0;
	i = 0;
	while (original[i])
	{
		if (ft_strlen(original[i]))
			elems++;
		i++;
	}
	return (elems);
}

char	**re_alloc_parse(char **original)
{
	t_re_alloc_var	va;

	va.i = 0;
	va.elems = 0;
	if (!original)
		return (NULL);
	va.elems = count_elems1(original);
	va.ret = malloc(sizeof(char *) * (va.elems + 1));
	if (!va.ret)
		return (NULL);
	va.i = 0;
	va.k = 0;
	while (va.i < va.elems)
	{
		while (!ft_strlen(original[va.k]) && original[va.k])
			va.k++;
		if (original[va.k])
			va.ret[va.i] = ft_strdup(original[va.k]);
		va.i++;
		va.k++;
	}
	va.ret[va.i] = NULL;
	free_array(original);
	return (va.ret);
}

int	check_builtinlst(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	else if (ft_strcmp(str, "absolute_path") == 0)
		return (1);
	else if (ft_strcmp(str, "testing") == 0)
		return (1);
	else if (ft_strcmp(str, "history") == 0)
		return (1);
	else
		return (0);
}

void	ft_lstbuiltcheck(void)
{
	t_linklis	*lst;

	lst = g_sh.ls_start;
	while (lst)
	{
		if (lst->content[0] && check_builtinlst(lst->content[0]))
			lst->builtin = 1;
		else
			lst->builtin = 0;
		lst = lst->next;
	}
}

void	ft_lstclear_zerolen(void)

{
	t_linklis	*lst;

	lst = g_sh.ls_start;
	while (lst)
	{
		lst->content = re_alloc_parse(lst->content);
		lst = lst->next;
	}
}
