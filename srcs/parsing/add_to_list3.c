/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_list3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 11:27:37 by tisantos          #+#    #+#             */
/*   Updated: 2021/04/28 11:29:03 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**ft_clsplit(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

int	che_open_quo(t_splvariab *varia, char t)
{
	if (t == '\"' && varia->double_q == 0 && varia->single_q == 0 )
		varia->double_q = 1;
	else if (t == '\"' && varia->double_q == 1 && varia->single_q == 0 )
		varia->double_q = 0;
	else if (t == '\'' && varia->single_q == 0 && varia->double_q == 0)
		varia->single_q = 1;
	else if (t == '\'' && varia->single_q == 1 && varia->double_q == 0 )
		varia->single_q = 0;
	if (varia->double_q == 0 && varia->single_q == 0)
		return (1);
	else
		return (0);
}

static unsigned int	ft_get_splnb(char const *s,
	const char *delimiters, t_splvariab *variab)
{
	unsigned int	i;
	unsigned int	nb_strs;
	int				k;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && ft_strchr(delimiters, s[i]))
		i++;
	while (s[i])
	{
		k = che_open_quo(variab, s[i]);
		if (ft_strchr(delimiters, s[i]) && k)
		{
			nb_strs++;
			while (s[i] && ft_strchr(delimiters, s[i]))
				i++;
			continue ;
		}
		i++;
	}
	if (!ft_strchr(delimiters, s[i - 1]))
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str1(char **next_str, unsigned int *next_str_len,
					const char *delimiters, t_splvariab *varia)
{
	unsigned int	i;
	char			k;
	int				a;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && ft_strchr(delimiters, **next_str))
		(*next_str)++;
	while ((*next_str)[i])
	{
		k = (*next_str)[i];
		a = che_open_quo(varia, k);
		if (a && ft_strchr(delimiters, (*next_str)[i]))
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split_igquo(char const *s, const char *delimiters)
{
	t_splvariab	var;

	var.double_q = 0;
	var.single_q = 0;
	var.nb_strs = ft_get_splnb(s, delimiters, &var);
	var.single_q = 0;
	var.double_q = 0;
	var.tab = malloc(sizeof(char *) * (var.nb_strs + 1));
	if (var.tab == NULL)
		return (NULL);
	var.i = 0;
	var.next_str = (char *)s;
	var.next_str_len = 0;
	while (var.i < var.nb_strs)
	{
		ft_get_next_str1(&var.next_str, &var.next_str_len, delimiters, &var);
		var.tab[var.i] = malloc(sizeof(char) * (var.next_str_len + 1));
		if (var.tab[var.i] == NULL)
			return (ft_clsplit(var.tab));
		ft_strlcpy(var.tab[var.i], var.next_str, var.next_str_len + 1);
		var.i++;
	}
	var.tab[var.i] = NULL;
	return (var.tab);
}
