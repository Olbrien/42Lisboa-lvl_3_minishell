/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_simple_cmd4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 04:23:22 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:43:12 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

t_simplecommand	*debug_simple_commands2(t_simplecommand *temp, int i)
{
	while (temp->outfile[i] != NULL)
	{
		printf("Outfile[%i] = %s \n", i, temp->outfile[i]);
		i++;
	}
	if (i == 0)
		printf("Outfile[%i] = %s \n", i, temp->outfile[i]);
	else
		printf("Outfile[%i] = %s \n", i, temp->outfile[i]);
	printf("Outfiles = %i \n", temp->outfiles);
	printf("Append = %i \n", temp->append);
	i = 0;
	while (temp->infile[i] != NULL)
	{
		printf("Infile[%i] = %s \n", i, temp->infile[i]);
		i++;
	}
	if (i == 0)
		printf("Infile[%i] = %s \n", i, temp->infile[i]);
	else
		printf("Infile[%i] = %s \n", i, temp->infile[i]);
	printf("Infiles = %i \n", temp->infiles);
	return (temp);
}

void	debug_simple_commands(void)
{
	t_simplecommand	*temp;
	int				i;
	int				a;

	a = 0;
	temp = g_sh.simple_cmd;
	while (temp != NULL)
	{
		i = 0;
		printf("\n");
		printf("\n------------SIMPLE COMMAND[%i]------------\n", a);
		while (temp->command[i] != NULL)
		{
			printf("Command[%i] = %s \n", i, temp->command[i]);
			i++;
		}
		printf("Command[%i] = %s \n", i, temp->command[i]);
		if (i == 0)
			printf("Command = (null)\n");
		printf("Builtin = %i \n", temp->builtin);
		i = 0;
		temp = debug_simple_commands2(temp, i);
		temp = temp->next;
		a++;
	}
}

void	ft_lstclear_simple_struct(t_simplecommand **lst)
{
	t_simplecommand	*current;
	t_simplecommand	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free_array(current->command);
		free_array(current->infile);
		free_array(current->outfile);
		free(current);
		current = next;
	}
	*lst = NULL;
}

char	**new_array_array(char **args)
{
	int		a;
	int		i;
	char	**temp;

	a = 0;
	i = 0;
	if (args == NULL)
	{
		temp = malloc(sizeof(char *) * 1);
		temp[0] = NULL;
		return (temp);
	}
	while (args[a] != NULL)
		a++;
	temp = malloc(sizeof(char *) * (a + 1));
	if (temp == NULL)
		return (NULL);
	while (args[i] != NULL)
	{
		temp[i] = ft_strdup(args[i]);
		i++;
	}
	temp[i] = NULL;
	return (temp);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*string;
	int		len;
	int		i;
	int		b;

	i = 0;
	b = 0;
	if (!s1)
		return (NULL);
	if (!s2 && s1)
		return ((char *)s1);
	len = strlen(s1) + strlen(s2);
	string = malloc(len + 1 * sizeof(string));
	if (string == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[b] != '\0')
		string[i++] = s2[b++];
	string[i] = '\0';
	free(s1);
	return (string);
}
