/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/18 12:03:10 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir(t_cmd *cmd)
{
    cmd->fd[cmd->io] = ft_open(cmd->file, cmd->io);
    if (cmd->fd[cmd->io] < 0)
	  err_msg(RED"Error : open"RESET);
	if (dup2(cmd->fd[cmd->io], cmd->io) == -1)
	{
		perror ("dup2");
		return ;
	}
    close(cmd->fd[cmd->io]);
}

char	*check_access(char *path, char *bin)
{
	char	*tmp;
	int		i;
	int		j;

	if (!path || !bin)
		return (NULL);
	tmp = (char *)ft_calloc((ft_strlen(path)  \
	+ ft_strlen(bin) + 2), sizeof(char));
	if (!tmp)
		return (NULL);
	i = -1;
	while (path[++i])
		tmp[i] = path[i];
	tmp[i] = '/';
	j = 0;
	i++;
	while (bin[j])
	  tmp[i++] = bin[j++];
	tmp[i] = 0;
	if (!access(tmp, F_OK | X_OK))
		return (tmp);
	free (tmp);
	return (NULL);
}

void execute_relative_or_absolute(t_cmd *cmd, t_data *data)
{
	execve(cmd->cmd[0], cmd->cmd, data->env);
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	data->status = 1;
}

void execute_path(t_cmd *cmd, t_data *data)
{
	int		i;
	
	i = -1;
	while (data->path[++i] != 0)
	  execve(check_access(data->path[i], cmd->cmd[0]), \
	 cmd->cmd, data->env);
	ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	data->status = 1;
}

int	bin_execute(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	if (cmd->type == 5)
		pipe (cmd->fd);
	pid = fork();
	if (pid < 0)
	  return(err_msg(RED"errrr fork"RESET));
	if (!pid)
	{
		if (cmd->type == 5)
		{
		  dup2(cmd->fd[1], 1);
		  close (cmd->fd[0]); // close read
		}
	 	if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		  execute_relative_or_absolute(cmd, data);
		else
		  execute_path(cmd, data);
		exit (EXIT_SUCCESS);
	}
	else
	{
	  waitpid(pid, &data->status, 0);
	  if (cmd->type == 5)
	  {
		  dup2(cmd->fd[0], 0);
		  close (cmd->fd[1]); // close write
	  }
	}
  return (0);
}
