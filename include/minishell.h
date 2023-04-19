/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 09:41:17 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/18 14:48:04 by Dugonzal         ###   ########.fr       */
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
//typedef struct s_cmd
//{
//	char *line;
///} t_cmd;

typedef struct s_data
{
	char			*cmd;
	int				quotes;
	char			**quotes_char;
	char			**path;
	char			**bufer;
	char			**env;
	char			*line;
	pid_t			pid;
	int				status;
} t_data;

void	handler(int sig, siginfo_t *info, void *context);
void	signals(void);
void	parser(t_data *data);
char	*prompt(void);
void	bin_execute(t_data *mini);
// builtins
int		verify_quotes(t_data *data);
void	ft_exit(t_data  *data);
void print(char **str);
#endif
