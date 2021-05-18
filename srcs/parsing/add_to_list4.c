/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:29:40 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:29:59 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	is_a_shell_symbol(char a, char a1)
{
	if (a == '>' && a1 == '>')
		return (1);
	if (a == '|')
		return (1);
	if (a == '<')
		return (1);
	if (a == '>')
		return (1);
	return (0);
}

int	chck_iespac(char s1, char s)
{
	if (!ft_strchr(SHELL_DELIMITERS, s1) && s == '\"')
		return (1);
	else if (!ft_strchr(SHELL_DELIMITERS, s1) && s == '\'')
		return (1);
	else
		return (0);
}

int	check_inside_symbols(t_splvariab *var, char *str)
{
	int	i;

	(void)var;
	i = 0;
	{
		if (str[i + 1] && is_a_shell_symbol(str[i], str[i + 1]))
			return (1);
	}
	return (0);
}

void	chck_begend_symbols2(int i, char *pt)
{
	while (pt[i] && ft_strchr(SHELL_DELIMITERS, pt[i]))
		i++;
	if (ft_strchr("|><", pt[i]))
	{
		if (!g_sh.error_log)
			g_sh.error_log = ft_errstr(pt[i]);
		g_sh.error = 1;
	}
	i = ft_strlen(pt) - 1;
	while (pt[i] && i > 0 && ft_strchr(SHELL_DELIMITERS, pt[i]))
		i--;
	if (ft_strchr("|><", pt[i]))
	{
		if (!g_sh.error_log)
			g_sh.error_log = ft_errstr(pt[i]);
		g_sh.error = 1;
	}
}

void	chck_begend_symbols(void)
{
	t_linklis	*lst;
	int			i;
	char		*pt;
	char		*old;

	lst = g_sh.ls_start;
	while (lst)
	{
		pt = lst->pre_split;
		i = 0;
		if (pt[i])
			chck_begend_symbols2(i, pt);
		else
		{
			if (!g_sh.error_log)
				g_sh.error_log = ft_strdup(g_sh.cmd_tables[g_sh.actind]
						+ ft_strlen(old));
			g_sh.error = 1;
		}
		lst = lst->next;
		old = pt;
	}
}
