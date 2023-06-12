/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/12 12:26:04 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void err_open(int fd)
{
	if (fd < 0)
	{
		unlink("heredoc");
		return ;
	}
}

void	heredoc(char *intfile, t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = ft_open("heredoc", 1);
	if (fd < 0)
	  return (err_open(fd));
	while (42)
	{
		line = readline(GREEN"🙂🚀❯ "RESET);
		if (!line)
		{
			ft_printf (RED"\nError: heredoc readline\n"RESET);
			break ;
		}
		if (!ft_strncmp(intfile, line, ft_strlen(intfile)))
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
	cmd->intfile = ft_open("heredoc", 0);
	if (cmd->intfile < 0)
	  return (err_open(fd));
	unlink("heredoc");
}

int	redir_in_util(t_cmd *cmd, char *intfile)
{
	cmd->intfile = ft_open(intfile, 0);
	if (cmd->intfile < 0)	
	  return (1);
	if (dup2(cmd->intfile, 0) < 0)
		return (1);
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	int		i;
	int		j;


	i = 0;
	while (cmd->cmd[i])
	{
		j = -1;
	//	printf ("->[%d] [%s]<-\n", i, cmd->cmd[i]);
		while (cmd->cmd[i][++j])
		{
			if (cmd->cmd[i][j] == '<' && ft_strlen(cmd->cmd[i]) == 1)
			{
				cmd->cmd[i] = NULL;
				if (redir_in_util(cmd, cmd->cmd[i + 1]))
					return (1);
				cmd->cmd[i + 1] = NULL;
				if (cmd->cmd[i + 2]) //&& (cmd->cmd[i + 2][0] != '<'))
				{
					cmd->cmd[i] = cmd->cmd[i + 2];
					cmd->cmd[i + 2] = NULL;
				}
				i += 2;
				break;
			}
		}
		i++;
	}
	//print (cmd->cmd);
	return (0);
}
