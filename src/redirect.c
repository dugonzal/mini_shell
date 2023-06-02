/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/02 16:44:55 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int redir_in(t_cmd *cmd, char **str)
{
	if (search(str[0], '<') && !str[0][1])
		cmd->fd[0] = ft_open(str[1], 0);
	else if (search(str[0], '<') && str[0][1] == '<')
		printf ("heredoc<");
	if (cmd->fd[0] < 0)
		return (1);
	str[0] = NULL;
	str[1] = NULL;
	ft_dup2(cmd->fd, 0);
	return (0);
}

int redir_out(t_cmd *cmd, char **str)
{
	if (search(str[0], '>') && !str[0][1])
		cmd->fd[1] = ft_open(str[1], 1);
	else if (search(str[0], '>') && str[0][1] == '>')
		cmd->fd[1] = ft_open(str[1], 2);
	if (cmd->fd[1] < 0)
		return (1);
	str[0] = NULL;
	str[1] = NULL;
	if (ft_dup2(cmd->fd, 1))
		return (1);	
	return (0);
}
	// tendria que dividirlo en dos segementos de redireccion
	// las de entrada < << || o salida > >>
	// stdinfile, stdoutfile, stderrfile
	// si no hay redirecciones, no hace nada
	// 1 = stdout 2 = stderr 0 = stdin
int redir(t_cmd *cmd)
{
	int i;

	i = -1;
	while (cmd->cmd[++i])
		if (search(cmd->cmd[i], '<'))
			if (redir_in(cmd, &cmd->cmd[i]))
				return (1);
	i = -1;
	while (cmd->cmd[++i])
		if (search(cmd->cmd[i], '>'))
			if (redir_out(cmd, &cmd->cmd[i]))
				return (1);

	return (0);	
}










