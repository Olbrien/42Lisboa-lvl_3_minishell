/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 03:19:59 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:20:43 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	change_dir(char *path)
{
	char	*buf;
	int		ret;

	if (!ft_strncmp(path, "~", 1))
		buf = ft_strdup(env_isex_elem("HOME"));
	else if (!ft_strncmp(path, "-", 1))
		buf = ft_strdup(env_isex_elem("OLDPWD"));
	else
		buf = ft_strdup(path);
	if (!buf)
		return (-1);
	ret = chdir(buf);
	if (ret != -1 && !ft_strncmp(path, "-", 1))
		ft_pwd();
	free(buf);
	return (ret);
}

int	ft_cd(char **content)
{
	char	pwd[1001];

	if (!content[1] || !ft_strlen(content[1]))
	{
		change_dir("~");
		env_var_update("OLDPWD", "PWD", 1);
		return (-1);
	}
	if (content[2])
	{
		printf("bash: cd: Too many arguments\n");
		return (-1);
	}
	if (!ft_strcmp(content[1], "~") && ft_strlen(env_isex_elem ("HOME")))
		change_dir("~");
	else if (change_dir(content[1]) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", content[1]);
		return (-1);
	}
	getcwd(pwd, 1000);
	env_var_update("OLDPWD", "PWD", 1);
	env_var_update("PWD", pwd, 0);
	return (0);
}
