/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/03 14:08:23 by Dugonzal         ###   ########.fr       */
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

typedef struct s_cmd
{
	pid_t			*pid; // si lo declaro como un puntero tengo que hacer malloc
	char			**cmd;
	struct s_cmd	*next;

} t_cmd;

typedef struct s_data
{
	// deberia tener una variable que de las cadenas de la linea de comando
	char			*line;
	char			**bufer;
	char			**cmd;
	char			**path;
	char			**env;
	int				*fd;
	int				status;
	pid_t 			pid; // temporal
	int				pipe;
	int				redir;
	//struct s_cmd	s_cmd;
} t_data;

void	handler(int sig, siginfo_t *info, void *context);
void	signals(void);
void	parser(t_data *data);
char	*prompt(void);
void	bin_execute(t_data *mini);
// builtins
int		verify_quotes(t_data *data);
void	ft_exit(t_data  *data);
void	print(char **str);

// utils
void	*free_array(char **array);
void	print(char **str);
char	*fun_check(char *str);
int		search(char *set, char c);

// parser
int		lexer(t_data *data);
char	**split_token(char *prompt, char *set, char *quotes, char *special);
int		count_word(char *prompt, char *set, char *quotes, char *specials);
int		quotes_token(char *str, char quote);
int		caracteres_token(char *prompt, char *set, char *quotes, char *specials);
int		specials_token(char *prompt);

// parser utils

int		err_msg(char *str);
int		check_redir(char **prompt, char redir);
int		check_pipe(char **prompt, char pipe);
int		check_quotes(char **prompt, char *quotes);

#endif
