/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/05 11:16:27 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc(t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = ft_open("heredoc", 1);
	while (42)
	{
		line = readline(GREEN"🚀➤  "RESET);
		if (!ft_strncmp(cmd->cmd[2], line, ft_strlen(cmd->cmd[2])))
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
	cmd->intfile = ft_open("heredoc", 0);
	unlink("heredoc");
}

int	redir_in(t_cmd *cmd, char *str, char *intfile)
{
	if (search(str, '<') && !str[1])
		cmd->intfile = ft_open(intfile, 0);
	else if (search(str, '<') && str[1] == '<')
		heredoc(cmd);
	if (cmd->intfile < 1)
		return (1);
	if (dup2(cmd->intfile, 0) < 0)
		return (1);
	return (0);
}

int	redir_out(t_cmd *cmd, char *str, char *outfile)
{
	if (search(str, '>') && !str[1])
		cmd->outfile = ft_open(outfile, 1);
	else if (search(str, '>') && str[1] == '>')
		cmd->outfile = ft_open(outfile, 2);
	if (cmd->outfile < 0)
		return (1);
	if (dup2(cmd->outfile, 1) < 0)
		return (1);
	return (0);
}

int	redir_controller(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd->cmd[++i])
	{
		if (search(cmd->cmd[i], '>') \
		&& (!search(cmd->cmd[i], '\'') && !search(cmd->cmd[i], '\"')))
		{
			if (redir_out(cmd, cmd->cmd[i], cmd->cmd[i + 1]))
				return (1);
			cmd->cmd[i] = NULL;
			cmd->cmd[i + 1] = NULL;
		}
	}
	return (0);
}

int	redir(t_cmd *cmd)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (cmd->cmd[++i])
	{
		if (search(cmd->cmd[i], '<') && (!search(cmd->cmd[i], '\'') \
		&& !search(cmd->cmd[i], '\"')))
		{
			flag = i;
			if (redir_in(cmd, cmd->cmd[i], cmd->cmd[i + 1]))
				return (1);
			break ;
		}
	}
	redir_controller(cmd);
	if (flag)
	{
		cmd->cmd[flag] = NULL;
		cmd->cmd[flag + 1] = NULL;
	}
	return (0);
}
