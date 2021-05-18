/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tables3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 17:20:10 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:36 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	remove_cmd_blanks(void)
{
	int	i;
	int	a;
	int	not_null;

	i = 0;
	a = 0;
	not_null = 0;
	while (g_sh.cmd_tables[i] != NULL)
		i++;
	i -= 1;
	while (g_sh.cmd_tables[i][a] != '\0')
		if (g_sh.cmd_tables[i][a++] != ' ')
			not_null++;
	if (not_null == 0)
	{
		free(g_sh.cmd_tables[i]);
		g_sh.cmd_tables[i] = NULL;
	}
	i = 0;
	remove_cmd_blanks2();
}

void	remove_cmd_semicolons(void)
{
	int	i;

	i = 0;
	while (g_sh.cmd_tables[i] != NULL)
	{
		if (g_sh.cmd_tables[i][ft_strlen(g_sh.cmd_tables[i]) - 1] == ';')
			g_sh.cmd_tables[i][ft_strlen(g_sh.cmd_tables[i]) - 1] = '\0';
		i++;
	}
	i = 0;
}

int	final_cmd_error_handling(int i, int a, int c)
{
	while (g_sh.cmd_tables[i] != NULL)
	{
		a = 0;
		c = 0;
		if (g_sh.cmd_tables[i][0] == ';')
		{
			syntax_error(1);
			return (0);
		}
		while (g_sh.cmd_tables[i][a] != '\0')
		{
			if (g_sh.cmd_tables[i][a] != ' '
				&& g_sh.cmd_tables[i][a] != ';')
				c++;
			if (g_sh.cmd_tables[i][a] == ';' && c == 0)
			{
				syntax_error(1);
				return (0);
			}
			a++;
		}
		i++;
	}
	return (1);
}

void	initial_cmd_error_handling2(int *semicolon_location,
										int semicolon_count)
{
	if (semicolon_count == 1)
		syntax_error(1);
	else if (semicolon_count > 1)
	{
		if (semicolon_location[1] == 1)
			syntax_error(2);
		else
			syntax_error(1);
	}
}

int	initial_cmd_error_handling(int *semicolon_location, int semicolon_count)
{
	int	i;

	i = 0;
	if (semicolon_location[0] == 0)
	{
		initial_cmd_error_handling2(semicolon_location, semicolon_count);
		return (0);
	}
	while (i < semicolon_count)
	{
		if ((semicolon_location[i + 1] - semicolon_location[i]) == 1)
		{
			syntax_error(2);
			return (0);
		}
		i++;
	}
	return (1);
}
