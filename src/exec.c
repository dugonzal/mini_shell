/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/13 16:03:58 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir(t_cmd *cmd)
{
    cmd->fd[cmd->io] = ft_open(cmd->file, cmd->io);
    if (cmd->fd[cmd->io] < 0 || \
	dup2(cmd->fd[cmd->io], cmd->io) == -1)
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
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(bin) + 2));
	if (!tmp)
		return (NULL);
	j = 0;
	i = -1;
	while (path[++i])
		tmp[i] = path[i];
	tmp[i] = '/';
	i++;
	while (bin[j])
	  tmp[i++] = bin[j++];
	tmp[i] = 0;
	if (!access(tmp, 0))
		return (tmp);
	free (tmp);
	return (NULL);
}

int	bin_execute(t_cmd *cmd, t_data *data)
{
	int		status;
	int		i;
	pid_t	pid;

	status = 0;
	pid = fork();
	if (pid < 0)
		return(err_msg(RED"errrr fork"RESET));
	if (!pid)
	{
		if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		{
			execve(cmd->cmd[0], cmd->cmd, data->env);
			ft_putendl_fd(RED"Error : comand no found"RESET, 2);
		}
		else
		{
			i = -1;
			while (data->path[++i] != 0)
				execve(check_access(data->path[i], cmd->cmd[0]), \
		   cmd->cmd, data->env);
			ft_putendl_fd(RED"Error : comand no found"RESET, 2);
		}
		ft_putendl_fd(RED"Error : comand no found"RESET, 2);
	}
	else
	  waitpid(pid, &status, 0);
  return (0);
}
