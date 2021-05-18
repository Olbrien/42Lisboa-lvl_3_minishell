/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisantos <tisantos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:59:14 by tisantos          #+#    #+#             */
/*   Updated: 2021/05/18 18:39:38 by tisantos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "./libft/libft.h"

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
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <dirent.h>

# define SHELL_DELIMITERS " \t\r\n\a"
# define DELIMETERS2 " \t\r\n\a\'\""
# define DELIMITERS3 " \t\r\n\a\'\"/"
# define OPEN_QUOTE_EC "\'\""

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_norminette_struct
{
	int				i;
	int				a;
	int				b;
	int				c;
	int				s;
	int				single_q;
	int				double_q;
	int				copy;
	DIR				*dir;
	struct dirent	*dirent;
	int				nb_char_read;
}		t_norminette_struct;

typedef struct s_complicated_exec
{
	int			tmpin;
	int			tmpout;

	int			fdin;
	int			fdout;

	int			ret;

	int			fdpipe[2];

}				t_complicated_exec;

typedef struct s_simplecommand_temp
{
	char		**temp_command;
	char		**temp_infile;
	char		**temp_outfile;
	int			temp_builtin;

	int			temp_outfiles;
	int			temp_infiles;

	int			temp_append;

}		t_simplecommand_temp;

typedef struct s_simplecommand
{
	char					**command;
	char					**outfile;
	char					**infile;
	int						builtin;

	int						outfiles;
	int						infiles;
	int						append;

	struct s_simplecommand	*next;

}				t_simplecommand;

typedef struct s_re_alloc_var
{
	int		elems;
	int		i;
	int		k;
	char	**ret;
}				t_re_alloc_var;

typedef struct s_fou_env_var
{
	int		i;
	int		k;
	int		l;
	int		old_index;
	char	**ret;
	char	*search;
	char	temp[1001];
}				t_fou_env_var;

typedef struct s_env_rm_vars
{
	int		a;
	int		i;
	int		k;
	char	**temp;
	char	*set_equal;
}				t_env_rm_vars;

typedef struct s_built_ex_var
{
	char	*elem;
	char	*set;
	int		i;
}				t_built_ex_var;

typedef struct s_splvariab
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;
	int				single_q;
	int				double_q;
	int				its_clos;

}				t_splvariab;

typedef struct s_linklis
{
	char				*pre_split;
	char				**content;
	int					type;
	int					builtin;
	struct s_linklis	*next;
}				t_linklis;

typedef struct s_var_seplink
{
	int		i;
	int		s;
	int		single_q;
	int		double_q;
	char	n;
}				t_var_seplink;

typedef struct s_var_add_tlis
{
	int		i;
	t_list	*temp;
	char	*aux;
	int		start;
	int		last;
	int		type;
}			t_var_add_tlis;

typedef struct s_minishell
{
	t_linklis		*ls_start;
	t_simplecommand	*simple_cmd;

	char			*line;
	char			**cmd_tables;
	char			**args;

	char			**env;

	int				status;
	int				isdebugger;

	int				absolute_path;
	int				testing;

	char			**history;
	int				history_len;
	int				current_history;

	pid_t			pid;

	int				error;
	char			*error_log;
	int				actind;

	int				islinux;

	int				dollar_error;
	int				first_error;

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

}					t_minishell;

t_minishell	g_sh;

void			shell_prompt(void);
int				shell_prompt2(int norm, char **buf);
void			shell_prompt3(char *buf, int i);

void			syntax_error(int value);
int				initial_cmd_error_handling(int *semicolon_location,
					int semicolon_count);
int				final_cmd_error_handling(int i, int a, int c);
void			remove_cmd_semicolons(void);
void			remove_cmd_blanks(void);
void			syntax_error(int value);
void			remove_cmd_blanks2(void);

void			exec_command(void);
void			simple_execute(t_linklis *list);

void			complicated_execute(t_simplecommand *simple_cmd);
int				check_infile(t_simplecommand *smp_cmd);
int				check_outfile(t_simplecommand *smp_cmd);
int				take_infile(t_simplecommand *smp_cmd, t_complicated_exec *norm);
int				take_outfile(t_simplecommand *smp_cmd);

void			run_builtin_complicated(t_simplecommand *lista);
int				check_builtin_no_fork(t_simplecommand **lista);
t_simplecommand	*remove_quotation_marks(t_simplecommand *simple_cmd);
t_simplecommand	*remove_single_quotation_marks(t_simplecommand *simple_cmd);
int				infile_stuff(t_simplecommand **simple_cmd,
					t_complicated_exec *norm);
char			*get_path(char *command);

void			ft_debugger(void);
void			ft_absolute_path(void);
void			ft_testing(void);
void			ft_history(void);
void			ft_exit(char **content);
int				ft_pwd(void);
int				ft_echo(char **content);
void			ft_env(void);
int				ft_cd(char **content);
int				ft_export(char **content);
int				ft_unset(char **content);
void			ft_error(void);
void			ft_putnstr2(t_splvariab	*varia, char *str, int n, int i);
int				its_open_quo(t_splvariab *varia, char t);

int				cmd_parsing(void);
int				process_cmd_tables(void);

void			save_history(void);
char			**save_env(char **env);

int				*add_int_to_arr(int *array, int location, int count);
char			**add_str_to_arrarr(char **array, char *string);
int				only_spaces(char *line);
void			debug_command_table(int a);
char			*ft_errstr(char c);

void			sig_int(int signo);
void			sig_quit(int signo);

char			**ft_aloc_env(char **env);
char			**ft_split_igquo(char const *s, const char *delimiters);
int				chck_iespac(char s1, char s);
int				add_to_list(int index);
void			ft_lstspli(void);
void			ft_lsttrim(void);
void			ft_linklstclear(t_linklis **lst);
int				is_separator(char check, char check2, int *type);
void			add_var_init(t_var_add_tlis *va);
void			chck_dup_symbols(void);
void			chck_begend_symbols(void);
void			ft_lstbuiltcheck(void);
void			ft_lstclear_zerolen(void);
void			last_elem_lis(t_var_add_tlis *va, int index);
t_linklis		*ft_linknew(char *pre_split, int type);
void			ft_linkadd_back(t_linklis **lst, t_linklis *new);
int				sep_link_2(t_var_seplink *va, int *a, int index, int *type);
int				sep_link(int index, int *a, int *type);

void			add_to_simple_commands_list(void);
t_linklis		*if_redirections_infile(t_linklis *list,
					t_simplecommand_temp *temp, int b);
t_linklis		*if_redirections_outfile(t_linklis *list,
					t_simplecommand_temp *temp, int a);
void			if_redirections_outfile_2(t_linklis *list,
					t_simplecommand_temp *temp, int i);
void			if_redirections_infile_2(t_linklis *list,
					t_simplecommand_temp *temp, int i);

int				iterations_in_simple_command(t_linklis *list);
void			ft_lstnew_simple_add(t_simplecommand_temp add);
char			*ft_strjoin_free(char *s1, char const *s2);
char			**new_array_array(char **args);
void			ft_lstclear_simple_struct(t_simplecommand **lst);
void			debug_simple_commands(void);

void			free_global(char *f1, char *f2, char *f3, char *f4);
void			exit_finale(int free_list);

int				env_rm_elem (char *set);
char			*env_isex_elem (char *set);
int				env_var_update(char *set_tbc, char *new_ct, int is_env);
int				env_list_upd_elem(void);
void			found_env(char ***original);
void			found_env5(t_fou_env_var *var);
void			found_env6(t_fou_env_var *var);

int				ft_putint(int c);
void			init_termcaps(void);
void			turn_off_canonical_mode(void);
void			turn_on_canonical_mode(void);
int				has_history(void);
void			parse_input_history(char *buf, int *i);
int				is_up_down_arrow(char *buf);
void			delete_single_char(char *buf, int *i);
char			*ft_strcpy(char *dest, char *src);
void			shell_prompt_line(void);
int				func_case(int n, int *i);

void			loop_command_tables(void);

#endif
