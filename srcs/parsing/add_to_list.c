/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:26:39 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:36 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

t_linklis	*ft_linknew(char *pre_split, int type)
{
	t_linklis	*new;

	new = malloc(sizeof(t_linklis));
	if (new == NULL)
		return (NULL);
	if (new)
	{
		new->pre_split = pre_split;
		new->type = type;
		new->next = NULL;
	}
	return (new);
}

void	ft_linkadd_back(t_linklis **lst, t_linklis *new)
{
	t_linklis		*begin;

	if (!*lst)
	{
		(*lst) = new;
		return ;
	}
	if (lst && (*lst) && new)
	{
		begin = (*lst);
		if (begin == NULL)
			(*lst) = new;
		else
		{
			while (begin->next)
				begin = begin->next;
			begin->next = new;
		}
	}
}

int	sep_link_2(t_var_seplink *va, int *a, int index, int *type)
{
	*a = va->i;
	if (va->n == '\"' && va->double_q == 0 && va->single_q == 0 )
		va->double_q = 1;
	else if (va->n == '\"' && va->double_q == 1 && va->single_q == 0 )
		va->double_q = 0;
	else if (va->n == '\'' && va->single_q == 0 && va->double_q == 0)
		va->single_q = 1;
	else if (va->n == '\'' && va->single_q == 1 && va->double_q == 0 )
		va->single_q = 0;
	else if (is_separator(va->n, g_sh.cmd_tables[index][va->i + 1],
		type) && va->single_q == 0 && va->double_q == 0)
		return (va->i);
	va->i += 1;
	return (-1);
}

int	add_to_list_run(void)
{
	char	*err_message;

	err_message = "bash: syntax error near unexpected token";
	ft_lstspli();
	chck_begend_symbols();
	ft_lstclear_zerolen();
	env_list_upd_elem ();
	ft_lstbuiltcheck();
	if (g_sh.error == 1)
	{
		ft_linklstclear(&g_sh.ls_start);
		if (ft_strlen(g_sh.error_log) > 1)
			printf("%s `%.2s\'\n", err_message, g_sh.error_log);
		else
			printf("%s `%s'\n", err_message, g_sh.error_log);
		free (g_sh.error_log);
		return (0);
	}
	else
		return (1);
}

int	add_to_list(int index)
{
	t_var_add_tlis	va;

	add_var_init(&va);
	g_sh.actind = index;
	while (g_sh.cmd_tables[index][va.i])
	{
		va.last = sep_link(index, &va.i, &va.type);
		if (va.last > 0)
		{
			va.aux = ft_substr(g_sh.cmd_tables[index],
					va.start, va.last - va.start);
			ft_linkadd_back(&g_sh.ls_start, ft_linknew(va.aux, va.type));
			va.start = va.last + 1;
			if (va.type == 2)
			{
				va.start += 1;
				va.i++;
			}
		}
		if (!g_sh.cmd_tables[index][va.i + 1])
			last_elem_lis(&va, index);
		va.i++;
	}
	return (add_to_list_run());
}
