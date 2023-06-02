/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/02 16:20:42 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define BLUE "\033[0;34m"
# include "../libft/include/libft.h"
# include <dirent.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
typedef struct s_cmd
{
	pid_t			pid;
	int				pipe[2];// in out I/O
//	int				fd[2];
	char			**cmd;
	int				type;
	int				io;
	int 			status;
	struct s_cmd	*next;
	struct s_cmd	*back;
} t_cmd;

typedef struct s_data
{
	char 			*user;
	char			*line;
	char			**bufer;
	char			**path;
	char			**env;
	int 			fd[2]; // pointer copy_fd
	int				status;
} t_data;


void	signals(void);
char	*prompt(void);
int		bin_execute(t_cmd *cmd, t_data *data);

void	print(char **str);
int		verify_quotes(t_data *data);

void 	ft_dup2(int *fd, int io);
// builtins
int 	builtins(t_cmd *cmd, t_data *data);
int		ft_echo(char **str);
int		ft_pwd(void);
void	ft_execute_echo(char **cmd);
int		ft_export_general_builtin(char	**cmd, t_data *data);
int		ft_export_builtin_individual(char *cmd, t_data *data);
int		ft_exit(t_cmd  *cmd);
char	*ft_getenv_builtins(char	*cmd, char	**env); // funcion para crear enviroment, la voy a utilizar 
int		ft_cmd_isalnum(char	*str);
void	ft_invalid(char *c);
void	free_dblearray(void **array);
void	ft_echo_builtin(t_cmd *cmd);
int		ft_cd_builtin(t_cmd *cmd, t_data *data);
int		ft_unset_builtin(char	**cmd, char	***env);
void	env(char **env);
// utils
void	*free_array(char **array);
void	print(char **str);
char	*fun_check(char *str);
int		search(char *set, char c);
void	free_cmd(t_cmd *cmd);

//lexer
int		lexer(t_data *data);
char	**split_token(const char *prompt, char *set, char *quotes, char *special);
int		count_tokens(const char *prompt, char *set, char *quotes, char *specials);
int		quotes_token(const char *str, char quote, char *set);
int		characters_tokens(const char *prompt, char *set, char *quotes, char *specials);
int		specials_token(const char *prompt);

// lexer utils
int		err_msg(char *str);
int		check_redir(char **prompt, char redir);
int		check_pipe(char **prompt, char pipe);
int		check_quotes(char **prompt, char *quotes);
int 	check_semicolon(char **prompt);
int		expanser(t_data *data);
int		lexer_errors(char **str);

// parser
int		parser(t_data *data);
int		builtins(t_cmd *cmd, t_data *data);
void	handler_execute(t_data *data, t_cmd *cmd);

// parser utils
t_cmd	**last_back_node(t_cmd **cmd, t_cmd *new);
t_cmd	*new_node(char **str, int size);
int		size_node(char **str);
int		type(char *str);
int		ft_open(char *str, int i);
int		exec_redir(t_cmd *cmd);
void	seach_quotes(char **str, char *quotes);
void 	reset_fd(t_data *data);
void 	copy_fd(t_data *data);
int 	redir(t_cmd *cmd);


void 	get_env_and_path(t_data *data, char **env);
#endif
