/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:05:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/14 15:26:30 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	heredoc(char *intfile, t_cmd *cmd)
{
	int		fd;
	char	*line;

	fd = ft_open("heredoc", 1);
	if (fd < 0)
		return (err_open(fd));
	while (42)
	{
		line = readline(GREEN"🙂🚀❯ "RESET);
		if (!ft_strncmp(intfile, line, ft_strlen(intfile)))
			break ;
		ft_putendl_fd(line, fd);
	}
	close(fd);
	cmd->intfile = ft_open("heredoc", 0);
	if (cmd->intfile < 0 || dup2(cmd->intfile, 0) < 0)
		return (err_open(fd));
	unlink("heredoc");
	return (0);
}

int	output(t_cmd *cmd, int i, int j)
{
	int	fd;

	fd = ft_open(cmd->cmd[i + 1], j);
	if (fd < 0 || dup2(fd, 1) < 0)
		return (1);
	close(fd);
	return (0);
}

int	input(t_cmd *cmd, int i, int j)
{
	int	fd;

	fd = ft_open(cmd->cmd[i + 1], j);
	if (fd < 0 || dup2(fd, 0) < 0)
		return (1);
	close(fd);
	return (0);
}

int	redirect(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (cmd->cmd[i][1] == '<')
		{
			cmd->cmd[i] = NULL;
			if (cmd->cmd[i + 1])
				if (heredoc(cmd->cmd[i + 1], cmd))
					return (1);
			i++;
		}
		i++;
	}
	return (0);
}

int	handler_redirecciones(t_cmd *cmd, t_data *data)
{
	search_quotes(cmd, "\"\'");
	if (redirect(cmd))
		return (1);
	else if (builtins(cmd, data))
		;
	else
		bin_execute(cmd, data);
	return (0);
}
