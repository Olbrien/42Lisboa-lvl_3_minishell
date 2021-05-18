/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 02:40:31 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:45:12 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	delete_single_char(char *buf, int *i)
{
	ft_bzero(&buf[*i - 1], BUFSIZ - *i);
	tputs(g_sh.cursor_left, 1, ft_putint);
	tputs(g_sh.del_line, 1, ft_putint);
	shell_prompt_line();
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}

int	is_up_down_arrow(char *buf)
{
	if (ft_strcmp(g_sh.up_arrow, buf) == 0)
		return (1);
	else if (ft_strcmp(g_sh.down_arrow, buf) == 0)
		return (1);
	return (0);
}
