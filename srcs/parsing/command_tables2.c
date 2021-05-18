/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tables2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:36:21 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:35:00 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	split_cmd_tables3(int *semicolon_location, int i, int copy, int last)
{
	int	a;

	a = 0;
	g_sh.cmd_tables[i] = malloc(sizeof(char) * (ft_strlen(g_sh.line)
				+ 2));
	if (g_sh.cmd_tables[i] == NULL)
		return (0);
	if (last == 0)
	{
		while (copy <= semicolon_location[i])
			g_sh.cmd_tables[i][a++] = g_sh.line[copy++];
	}
	else
	{
		while (copy < (int)ft_strlen(g_sh.line))
			g_sh.cmd_tables[i][a++] = g_sh.line[copy++];
	}
	g_sh.cmd_tables[i][a] = '\0';
	return (copy);
}

int	split_cmd_tables2(int *semicolon_location, int semicolon_count, int copy)
{
	t_norminette_struct	n;

	n.i = 0;
	if (initial_cmd_error_handling(semicolon_location, semicolon_count) == 0)
	{
		free(semicolon_location);
		return (0);
	}
	g_sh.cmd_tables = malloc(sizeof(char *) * (semicolon_count + 2));
	if (g_sh.cmd_tables == NULL)
		return (0);
	while (n.i < semicolon_count)
		copy = split_cmd_tables3(semicolon_location, n.i++, copy, 0);
	if (copy < (int)ft_strlen(g_sh.line))
		copy = split_cmd_tables3(semicolon_location, n.i++, copy, 1);
	g_sh.cmd_tables[n.i] = NULL;
	if (final_cmd_error_handling(0, 0, 0) == 0)
	{
		free_global("cmd_tables", "empty", "empty", "empty");
		free(semicolon_location);
		return (0);
	}
	remove_cmd_semicolons();
	remove_cmd_blanks();
	return (1);
}

int	split_cmd_tables(int *semicolon_location, int semicolon_count)
{
	int	i;

	i = 0;
	if (semicolon_count == 0)
	{
		g_sh.cmd_tables = malloc(sizeof(char *) * 2);
		g_sh.cmd_tables[0] = ft_strdup(g_sh.line);
		g_sh.cmd_tables[1] = NULL;
		return (1);
	}
	else
	{
		if (split_cmd_tables2(semicolon_location, semicolon_count, 0) == 0)
			return (0);
	}
	return (1);
}

int	*separator_location(int *semi_locations, int *semi_count)
{
	t_norminette_struct	n;

	n.i = 0;
	n.s = 0;
	n.single_q = 0;
	n.double_q = 0;
	while (g_sh.line[n.i] != '\0')
	{
		if (g_sh.line[n.i] == '\"' && n.double_q == 0 && n.single_q == 0)
			n.double_q = 1;
		else if (g_sh.line[n.i] == '\"' && n.double_q == 1 && n.single_q == 0)
			n.double_q = 0;
		else if (g_sh.line[n.i] == '\'' && n.single_q == 0 && n.double_q == 0)
			n.single_q = 1;
		else if (g_sh.line[n.i] == '\'' && n.single_q == 1 && n.double_q == 0)
			n.single_q = 0;
		if (g_sh.line[n.i] == ';' && n.single_q == 0 && n.double_q == 0)
		{
			semi_locations = add_int_to_arr(semi_locations, n.i, n.s);
			n.s++;
		}
		n.i++;
	}
	*semi_count = n.s;
	return (semi_locations);
}

int	process_cmd_tables(void)
{
	int	*semicolon_location;
	int	semicolon_count;

	semicolon_location = malloc(sizeof(int ) * 2);
	semicolon_location[0] = '\0';
	semicolon_location = separator_location(semicolon_location,
			&semicolon_count);
	if (split_cmd_tables(semicolon_location, semicolon_count) == 0)
		return (0);
	free(semicolon_location);
	return (1);
}
