/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_simple_cmd2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:21:27 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/11 18:14:56 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	iterations_in_simple_command(t_linklis *list)
{
	int	i;

	i = 0;
	while (list != NULL && list->type != 8 && list->type != 1)
	{
		i++;
		list = list->next;
	}
	if (i > 0)
		i++;
	return (i);
}

void	if_redirections_infile_2(t_linklis *list,
											t_simplecommand_temp *temp, int i)
{
	int	a;

	while (list->content[i] != NULL)
	{
		a = 0;
		while (temp->temp_command[a] != NULL)
			a++;
		temp->temp_command[a] = ft_strdup(list->content[i]);
		temp->temp_command[a + 1] = NULL;
		i++;
	}
}

t_linklis	*if_redirections_infile(t_linklis *list,
											t_simplecommand_temp *temp, int b)
{
	int	i;

	i = 0;
	list = list->next;
	if (temp->temp_infile == NULL)
		temp->temp_infile = malloc(sizeof(char *) * 50);
	temp->temp_infiles++;
	temp->temp_infile[b] = ft_strdup(list->content[0]);
	temp->temp_infile[b + 1] = NULL;
	i = 1;
	if_redirections_infile_2(list, temp, i);
	return (list);
}

void	if_redirections_outfile_2(t_linklis *list,
											t_simplecommand_temp *temp, int i)
{
	int	a;

	while (list->content[i] != NULL)
	{
		a = 0;
		while (temp->temp_command[a] != NULL)
			a++;
		temp->temp_command[a] = ft_strdup(list->content[i]);
		temp->temp_command[a + 1] = NULL;
		i++;
	}
}

t_linklis	*if_redirections_outfile(t_linklis *list,
											t_simplecommand_temp *temp, int a)
{
	int	i;

	i = 1;
	if (list->type == 3)
		temp->temp_append = 0;
	else if (list->type == 2)
		temp->temp_append = 1;
	list = list->next;
	temp->temp_outfiles++;
	if (temp->temp_outfile == NULL)
		temp->temp_outfile = malloc(sizeof(char *) * 50);
	temp->temp_outfile[a] = ft_strdup(list->content[0]);
	temp->temp_outfile[a + 1] = NULL;
	if_redirections_outfile_2(list, temp, i);
	return (list);
}
