/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/06 18:06:51 by Dugonzal         ###   ########.fr       */
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

int	redir_in(t_cmd *cmd ,char *str, char *intfile)
{
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

int	count_re_size(char **str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][0] == 0)
			i++;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

void	re_size(t_cmd *cmd)
{
	char	**tmp;
	int		count;

	count = count_re_size(cmd->cmd);
	tmp = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (!tmp)
		return ;
	while (count--)
	{
		if (cmd->cmd[count][0] != 0)
			tmp[count] = ft_strdup(cmd->cmd[count]);
		else
			tmp[count] = NULL;
		free(cmd->cmd[count]);
	}
	tmp[count] = NULL;
	free(cmd->cmd);
	cmd->cmd = tmp;
}


int	redir(t_cmd *cmd)
{
	int		i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][0] == '<')
		{
			if (redir_in(cmd, cmd->cmd[i], cmd->cmd[i + 1]))
				return (1);
			ft_bzero(cmd->cmd[i], ft_strlen(cmd->cmd[i]));
			ft_bzero(cmd->cmd[i + 1], ft_strlen(cmd->cmd[i + 1]));
			break;
		}
		i++;
	}
//	re_size(cmd);
	return (0);
}
