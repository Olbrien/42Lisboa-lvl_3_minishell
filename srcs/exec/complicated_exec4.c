/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complicated_exec4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 04:03:15 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/17 15:28:01 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

t_simplecommand	*remove_single_quotation_marks(t_simplecommand *simple_cmd)
{
	t_norminette_struct	n;
	char				*temp;

	n.i = 0;
	n.a = 0;
	n.b = 1;
	temp = NULL;
	while (simple_cmd->command[n.i] != NULL)
	{
		if (simple_cmd->command[n.i][0] == '\'')
		{
			temp = malloc(sizeof(char) * ft_strlen(simple_cmd->command[n.i]));
			while (n.a < ((int)ft_strlen(simple_cmd->command[n.i])) - 2)
				temp[n.a++] = simple_cmd->command[n.i][n.b++];
			temp[n.a] = '\0';
			free(simple_cmd->command[n.i]);
			simple_cmd->command[n.i] = ft_strdup(temp);
			free(temp);
			n.a = 0;
			n.b = 1;
		}
		n.i++;
	}
	return (simple_cmd);
}

t_simplecommand	*remove_quotation_marks(t_simplecommand *simple_cmd)
{
	t_norminette_struct	n;
	char				*temp;

	n.i = 0;
	n.a = 0;
	n.b = 1;
	temp = NULL;
	while (simple_cmd->command[n.i] != NULL)
	{
		if (simple_cmd->command[n.i][0] == '\"')
		{
			temp = malloc(sizeof(char) * ft_strlen(simple_cmd->command[n.i]));
			while (n.a < (int)ft_strlen(simple_cmd->command[n.i]) - 2)
				temp[n.a++] = simple_cmd->command[n.i][n.b++];
			temp[n.a] = '\0';
			free(simple_cmd->command[n.i]);
			simple_cmd->command[n.i] = ft_strdup(temp);
			free(temp);
			n.a = 0;
			n.b = 1;
		}
		n.i++;
	}
	return (simple_cmd);
}

char	*get_path3(char *path, char *command)
{
	char	*path_send;
	int		size;
	int		i;
	int		a;

	i = 0;
	a = 0;
	size = ft_strlen(path) + ft_strlen(command) + 3;
	path_send = NULL;
	path_send = malloc(sizeof(char *) * size);
	while (path[i] != '\0')
		path_send[a++] = path[i++];
	i = 0;
	if (path_send[a] != '/')
		path_send[a++] = '/';
	while (command[i] != '\0')
		path_send[a++] = command[i++];
	path_send[a] = '\0';
	return (path_send);
}

char	*get_path2(char *command, char *bin_path, char **env_array)
{
	t_norminette_struct	norm;

	norm.i = 0;
	while (env_array[norm.i] != NULL)
	{
		norm.dir = opendir(env_array[norm.i]);
		if (norm.dir)
		{
			norm.dirent = readdir(norm.dir);
			while (norm.dirent)
			{
				if (ft_strcmp(norm.dirent->d_name, command) == 0)
				{
					bin_path = get_path3(env_array[norm.i], command);
					closedir(norm.dir);
					return (bin_path);
				}
				norm.dirent = readdir(norm.dir);
			}
			closedir(norm.dir);
		}
		norm.i++;
	}
	bin_path = ft_strdup("empty");
	return (bin_path);
}

char	*get_path(char *command)
{
	char	*bin_path;
	char	**env_array;
	char	*env;
	int		i;

	i = 0;
	bin_path = NULL;
	env = NULL;
	while (g_sh.env[i] != NULL)
	{
		if (ft_strncmp(g_sh.env[i], "PATH=", 5) == 0)
		{
			g_sh.env[i] += 5;
			env = g_sh.env[i];
			g_sh.env[i] -= 5;
			break ;
		}
		i++;
	}
	if (env == NULL)
		return (ft_strdup("empty"));
	env_array = ft_split(env, ':');
	bin_path = get_path2(command, bin_path, env_array);
	free_array(env_array);
	return (bin_path);
}
