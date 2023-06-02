/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/02 21:06:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void heredoc(t_cmd *cmd)
{
	int fd;
	char *line;

	fd = ft_open("tmp", 1);
	while (42)
	{
		line = readline(GREEN"🚀>  "RESET);
		if (!ft_strncmp(cmd->cmd[2], line, ft_strlen(cmd->cmd[2])))
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
	cmd->intfile = ft_open("tmp", 0);
}

int redir_in(t_cmd *cmd, char **str)
{
	if (search(str[0], '<') && !str[0][1])
		cmd->intfile = ft_open(str[1], 0);
	else if (search(str[0], '<') && str[0][1] == '<')
		heredoc(cmd);
	if (cmd->intfile < 0)
		return (1);
	str[0] = NULL;
	str[1] = NULL;
	if (dup2(cmd->intfile, 0) == -1)
		return (1);
	return (0);
}

int redir_out(t_cmd *cmd, char **str)
{
	if (search(str[0], '>') && !str[0][1])
		cmd->outfile = ft_open(str[1], 1);
	else if (search(str[0], '>') && str[0][1] == '>')
		cmd->outfile = ft_open(str[1], 2);
	if (cmd->outfile < 0)
		return (1);
	str[0] = NULL;
	str[1] = NULL;
	if (dup2(cmd->outfile, 1) == -1)
		return (1);
	return (0);
}

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










