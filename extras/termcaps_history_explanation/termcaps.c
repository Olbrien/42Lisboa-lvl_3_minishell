/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 18:38:30 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/16 03:45:07 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <termcap.h>
# include <fcntl.h>

int		ft_putint(int c);
void	prompt();
void	turn_on_canonical_mode();

/**************************************************************/
/*						Structs								  */
/**************************************************************/

typedef struct s_minishell
{
	int				islinux;

	char			*line; // Line you write on your stdin.

	char			**env;	 // Env.

	char			**history;	 // Saves the history of commands you typed.
	int				history_len; // How many commands you've typed.
	int				current_history;


	struct termios	old_term;
	struct termios	new_term;
	char			*buffer;

	char			*keys_on;
	char			*keys_off;
	char			*up_arrow;
	char			*down_arrow;
	char			*backspace;
	char			*del_line;
	char			*cursor_left;

	char			last_key_pressed;

} t_minishell;

t_minishell g_sh;



/**************************************************************/
/*						   Utils							  */
/**************************************************************/

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str_ptr;
	size_t			i;

	str_ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		str_ptr[i] = 0;
		i++;
	}
}
char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s[len] != '\0')
		len++;
	dest = malloc(sizeof(*dest) * len + 1);
	if (dest == NULL)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = (char *)str;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (NULL);
		i++;
		new_str++;
	}
	return (new_str);
}
int		ft_putint(int c)
{
	return (write(1, &c, 1));
}
int		ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == 0)
		return (-1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int		i;
	size_t	len;

	i = 0;
	len = n;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' && str2[i] != '\0' && len - 1 > 0)
	{
		if (str1[i] == str2[i])
		{
			i++;
			len--;
		}
		else
			break ;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
void	*ft_calloc(size_t nitems, size_t size)
{
	char			*arra;
	size_t			i;
	unsigned int	total;

	total = nitems * size;
	arra = malloc(nitems * size);
	if (arra == NULL)
		return (NULL);
	i = 0;
	while (total > 0)
	{
		arra[i] = 0;
		total--;
		i++;
	}
	return ((void *)arra);
}
void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void ft_exit()
{
	if (g_sh.keys_off)
		tputs(g_sh.keys_off, 1, ft_putint);
	if (g_sh.islinux == 0)
		free(g_sh.backspace);
	turn_on_canonical_mode();
}


/**************************************************************/
/*						   History							  */
/**************************************************************/

int		has_history()
{
	if (g_sh.history_len == 0)
		return(0);
	else
		return(1);
}
void	parse_input_history(char *buf, int *i)
{
	char	*input;
	int		only_up_arrow;

	only_up_arrow = 0;

	if (g_sh.current_history == g_sh.history_len)
		only_up_arrow = 1;
	if (has_history() == 0)
	{
		ft_bzero(&buf[*i], BUFSIZ - *i);
		return ;
	}
	if (ft_strcmp(g_sh.up_arrow, &buf[*i]) == 0)
	{
		if (g_sh.current_history > 0)
			g_sh.current_history--;
		input = g_sh.history[g_sh.current_history];
		tputs(g_sh.cursor_left, 1, ft_putint);
		tputs(g_sh.del_line, 1, ft_putint);
		prompt();
		ft_bzero(buf, BUFSIZ);
		ft_strcpy(buf, input);
		*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
	}
	else if (ft_strcmp(g_sh.down_arrow, &buf[*i]) == 0 && only_up_arrow == 0)
	{
		if (g_sh.current_history < g_sh.history_len - 1)
			g_sh.current_history++;
		input = g_sh.history[g_sh.current_history];
		tputs(g_sh.cursor_left, 1, ft_putint);
		tputs(g_sh.del_line, 1, ft_putint);
		prompt();
		ft_bzero(buf, BUFSIZ);
		ft_strcpy(buf, input);
		*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
	}
}
void	save_history()
{
	if (g_sh.history_len > 0 &&
		ft_strcmp(g_sh.history[g_sh.history_len - 1], g_sh.line) == 0)
		return;

	g_sh.history[g_sh.history_len] = ft_strdup(g_sh.line);
	g_sh.history_len++;
	g_sh.history[g_sh.history_len] = NULL;
}
void	set_history()
{
	g_sh.history = malloc(sizeof(char *) + 100);
	if (g_sh.history == NULL)
		return;
	g_sh.history_len = 0;
	g_sh.history[0] = NULL;
}


/**************************************************************/
/*						Termcaps Loop						  */
/**************************************************************/

void	turn_off_canonical_mode()
{
	g_sh.new_term = g_sh.old_term;
	g_sh.new_term.c_lflag &= ~ICANON;
	g_sh.new_term.c_lflag &= ~ECHO;
	g_sh.new_term.c_lflag &= ~ISIG;
	g_sh.new_term.c_cc[VMIN] = 1;
	g_sh.new_term.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_sh.new_term) == -1)
		ft_exit(EXIT_FAILURE);
}
void	turn_on_canonical_mode()
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_sh.old_term) == -1)
		ft_exit();
}

/**************************************************************/
/*						Termcaps Init						  */
/**************************************************************/

int		set_capabilities()
{
	g_sh.keys_on = tgetstr("ks", &g_sh.buffer);
	if (g_sh.keys_on)
		tputs(g_sh.keys_on, 1, ft_putint);
	g_sh.keys_off = tgetstr("ke", &g_sh.buffer);
	g_sh.up_arrow = tgetstr("ku", &g_sh.buffer);
	g_sh.down_arrow = tgetstr("kd", &g_sh.buffer);
	if (g_sh.islinux == 1)
		g_sh.backspace = tgetstr("kb", &g_sh.buffer);
	else
		g_sh.backspace = ft_strdup("\x7f");
	g_sh.del_line = tgetstr("dl", &g_sh.buffer);
	g_sh.cursor_left = tgetstr("cr", &g_sh.buffer);
	if ((!g_sh.keys_on) || (!g_sh.up_arrow) || (!g_sh.down_arrow)
		|| (!g_sh.backspace) || (!g_sh.del_line) || (!g_sh.keys_off)
		|| (!g_sh.cursor_left))
		return (0);
	else
		return (1);
}
char	*get_termtype()
{
	int i = 0;
	char *temp;

	temp = NULL;

	while (g_sh.env[i] != NULL)
	{
		if (ft_strncmp(g_sh.env[i], "TERM=", 5) == 0)
		{
			g_sh.env[i] += 5;
			temp = g_sh.env[i];
			break;
		}
		i++;
	}
	return (temp);
}
void	init_termcaps()
{
	char *term_type;
	int ret;

	if (isatty(STDIN_FILENO) != 1)
		exit(EXIT_FAILURE);

	if (tcgetattr(STDIN_FILENO, &g_sh.old_term) == -1)
		exit(EXIT_FAILURE);

	if (g_sh.islinux == 1)
	{
		g_sh.buffer = ft_calloc(2048, 1);
		if (g_sh.buffer == NULL)
			exit(EXIT_FAILURE);
	}

	term_type = get_termtype();
	if (term_type == NULL)
		exit(EXIT_FAILURE);

	ret = tgetent(g_sh.buffer, term_type);
	if (ret <= 0)
		exit(EXIT_FAILURE);
	else if (set_capabilities() == 0)
		exit(EXIT_FAILURE);

}


/**************************************************************/
/*						   Input							  */
/**************************************************************/

void	delete_single_char(char *buf, int *i)
{
	ft_bzero(&buf[*i - 1], BUFSIZ - *i);
	tputs(g_sh.cursor_left, 1, ft_putint);
	tputs(g_sh.del_line, 1, ft_putint);
	prompt();
	*i = write(STDOUT_FILENO, buf, ft_strlen(buf));
}
int		is_up_down_arrow(char *buf)
{
	if (ft_strcmp(g_sh.up_arrow, buf) == 0)
		return (1);
	else if (ft_strcmp(g_sh.down_arrow, buf) == 0)
		return (1);
	return (0);
}
void	get_input()
{
	char buf[BUFSIZ];
	int i;
	int nb_char_read;

	i = 0;

	ft_bzero(buf, BUFSIZ);
	g_sh.current_history = g_sh.history_len;

	while(!ft_strchr(buf, '\n'))
	{
		nb_char_read = read(STDIN_FILENO, &buf[i], BUFSIZ - i);
		if (is_up_down_arrow(&buf[i]))
			parse_input_history(buf, &i);
		else if (ft_strcmp(&buf[i], g_sh.backspace) == 0)
			delete_single_char(buf, &i);
		else if (nb_char_read > 1)
			ft_bzero(&buf[i], BUFSIZ - i);
		else
			i += write(STDOUT_FILENO, &buf[i], 1);
	}

	buf[i - 1] = '\0';
	g_sh.line = ft_strdup(buf);
	if (g_sh.line == NULL)
		ft_exit();
}
void	prompt()
{
	write(1, "\x1b[90mminishell\x1b[91m$ ", 22);
}

/**************************************************************/
/*						Main Stuff							  */
/**************************************************************/

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_sh.islinux = 1;
	g_sh.env = envp;
	set_history();

	init_termcaps();

	while (1)
	{
		turn_off_canonical_mode();
		g_sh.line = NULL;

		prompt();
		get_input();
		save_history();

		turn_on_canonical_mode();

		//execute();

		//**********************************************//
		if (strcmp(g_sh.line, "history") == 0)
		{
			for (size_t a = 0; g_sh.history[a] != NULL; a++)
				printf("%li  %s\n", a, g_sh.history[a]);
		}
		else if (strcmp(g_sh.line, "exit") == 0)
		{
			free(g_sh.line);
			free_array(g_sh.history);
			break;
		}
		free(g_sh.line);
	}
}
