/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/05 20:55:39 by Dugonzal         ###   ########.fr       */
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
	if (!intfile)
		intfile = ft_strdup("tmp");	
	cmd->intfile = ft_open(intfile, 0);
	if (search(str, '<') && str[1] == '<')
		cmd->intfile = ft_open(intfile, 0);	
	if (cmd->intfile < 1)
	{
		str = NULL;
		return (1);
	}
	if (dup2(cmd->intfile, 0) < 0)
		return (1);
	return (0);
}

int	redir(t_cmd *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	while (cmd->cmd[++i])
	{
		if (search(cmd->cmd[i], '<') && (!search(cmd->cmd[i], '\'') \
		&& !search(cmd->cmd[i], '\"')))
		{
			if (cmd->cmd[i + 1])
				tmp = ft_strdup(cmd->cmd[i + 1]);
			else
				tmp = NULL;
			if (redir_in(cmd, cmd->cmd[i], tmp))
				return (1);
			break ;
		}
	}
	return (0);
}
