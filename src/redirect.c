/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/09 16:50:06 by Dugonzal         ###   ########.fr       */
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

int	redir_in(t_cmd *cmd, char *intfile)
{
	cmd->intfile = ft_open(intfile, 0);
	if (cmd->intfile < 0)	
	{
	  printf ("sale por aqui");
	  return (1);
	}
	if (dup2(cmd->intfile, 0) < 0)
		return (1);
	return (0);
}

int	redir(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '<' && !cmd->cmd[i][1])
		{
			if (redir_in(cmd, cmd->cmd[i + 1]))
			{
				printf("sale poraaa \n");
				return (1);
			}
			cmd->cmd[i] = NULL;
			break;
		}
		i++;
	}
	return (0);
}
