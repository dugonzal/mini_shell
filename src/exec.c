/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/10 14:54:42 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_access(char *path, char *bin)
{
	char	*tmp;
	int		i;
	int		j;

	if (!path || !bin)
		return (NULL);
	tmp = (char *)ft_calloc((ft_strlen(path) \
	+ ft_strlen(bin) + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (path[++i])
		tmp[i] = path[i];
	tmp[i++] = '/';
	j = 0;
	while (bin[j])
		tmp[i++] = bin[j++];
	tmp[i] = 0;
	if (!access(tmp, F_OK | X_OK))
		return (tmp);
	free (tmp);
	return (NULL);
}

void	execute_relative_or_absolute(t_cmd *cmd, t_data *data)
{
	execve(cmd->cmd[0], cmd->cmd, data->env);
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	data->status = 127;
}

void	execute_path(t_cmd *cmd, t_data *data)
{
	int		i;

	i = -1;
	while (data->path[++i] != 0)
		execve(check_access(data->path[i], cmd->cmd[0]), \
		cmd->cmd, data->env);
	cmd->status = 127;
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
}

int	ft_dup2(int *fd, int io)
{
	if (dup2(fd[io], io) < 0)
		return (1);
	close(fd[io ^ 1]);
	return (0);
}

int	bin_execute(t_cmd *cmd, t_data *data)
{
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (err_msg(RED"errrr fork"RESET));
	if (!cmd->pid)
	{
		if (cmd->type == 5)
			if (ft_dup2 (cmd->pipe, 1))
				return (1);
		if (builtins(cmd, data))
			exit(data->status);
		else if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
			execute_relative_or_absolute(cmd, data);
		else
			execute_path(cmd, data);
		exit(EXIT_FAILURE);
	}
	if (cmd->pid > 0)
	{
		waitpid(cmd->pid, &cmd->status, 0);
		if (cmd->status == 256)
			cmd->status = 127;
	}
	return (0);
}
