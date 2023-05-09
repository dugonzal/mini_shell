/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/09 19:55:02 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir(t_cmd *cmd)
{
	int copy_fd;
    // Redirigir la salida al archivo
    cmd->fd[cmd->io] = ft_open(cmd->file, cmd->io);
    if (cmd->fd[cmd->io] < 0)
	{
        // Error al abrir el archivo de redirección
        perror("open");
        exit(EXIT_FAILURE);
    }
	copy_fd = dup(cmd->io);
      // Redirigir io archivo
      dup2(cmd->fd[cmd->io], cmd->io);
      close(cmd->fd[cmd->io]);
  if (cmd->file != NULL)
  {
	free(cmd->file);
	dup2 (copy_fd, cmd->io);  
	close (copy_fd);
  }
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
	char	*tmp;
	pid_t	pid;

	if (cmd->type == 5)
	  if (pipe (cmd->fd) == -1)
		  return (err_msg(RED"Error : pipe"RESET));
	status = 0;
	pid = fork();
	if (pid < 0)
		return(err_msg(RED"errrr fork"RESET));
	if (!pid)
	{
		if (cmd->file)
		  exec_redir(cmd);
		if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		{
			 execve(cmd->cmd[0], cmd->cmd, data->env);
			  ft_putstr_fd (RED"Error : comand no found\n"RESET, 2);
		}
		else
		{
			if (cmd->type == 5 && dup2 (cmd->fd[1], 1) != -1)
			{
				err_msg(RED"Error : dup2"RESET);
			}
			if 	(cmd->type == 5)
				close (cmd->fd[0]);
			i = -1;
			while (data->path[++i] != 0)
			{
				tmp = NULL;
				tmp = check_access(data->path[i], cmd->cmd[0]);
				execve(tmp, cmd->cmd, data->env);
				free (tmp);
			}
			ft_putendl_fd( RED"Error : comand no found"RESET, 2);
		}
	  printf ("Error : comand no found\n");
	  exit (EXIT_SUCCESS);
	}
	else
	{
		if (cmd->type == 5 && dup2 (cmd->fd[0], 0) != -1)
		  err_msg(RED"Error : dup2"RESET);	
	  if (cmd->type == 5)
		close (cmd->fd[1]);
	  waitpid(pid, &status, 0);
	}
  return (0);
}

int builtins(t_cmd *cmd, t_data *data)
{
  int fd;
  int stdout_copy;

  if (cmd->file != NULL)
  {
    fd = open(cmd->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
      perror("open");
      return 1;
    }

    stdout_copy = dup(STDOUT_FILENO);  // Hacer una copia del descriptor de archivo STDOUT_FILENO

    if (dup2(fd, STDOUT_FILENO) == -1)  // Redirigir la salida estándar al archivo
    {
      perror("dup2");
      return 1;
    }

    close(fd);
  }

  if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0])) && !cmd->cmd[1])
  {
    ft_exit(data);
    return (1);
  }
  else if (!ft_strncmp(cmd->cmd[0], "echo", ft_strlen(cmd->cmd[0])))
  {
    ft_echo(&cmd->cmd[1]);
    return (1);
  }

  if (cmd->file != NULL)
  {
    if (dup2(stdout_copy, STDOUT_FILENO) == -1)  // Restaurar el descriptor de archivo original de la salida estándar
    {
      perror("dup2");
      return 1;
    }
    close(stdout_copy);
  }

  return (0);
}

