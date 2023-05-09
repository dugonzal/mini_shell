/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/09 11:54:39 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_redir(t_cmd *cmd)
{
  if (cmd->file != NULL) 
  {
    // Redirigir la salida al archivo
    cmd->fd[cmd->io] = ft_open(cmd->file, cmd->io);
    if (cmd->fd[cmd->io] < 0)
	{
        // Error al abrir el archivo de redirección
        perror("open");
        exit(EXIT_FAILURE);
    }
      // Redirigir io archivo
      dup2(cmd->fd[cmd->io], cmd->io);
      close(cmd->fd[cmd->io]);
	  free(cmd->file);
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

/// @brief
/// @param mini
int	bin_execute(t_cmd *cmd, t_data *data)
{
	int		error;
	int		i;
	char	*tmp;
	pid_t	pid;

	error = 0;
//	if (cmd->type == 5)
//	  if (pipe (cmd->fd) == -1)
//		  return (err_msg(RED"Error : pipe"RESET));

	pid = fork();
	if (pid < 0)
		return(err_msg(RED"errrr fork"RESET));
	if (!pid)
	{
		exec_redir(cmd);
		if (cmd->cmd[0][0] == '.' || cmd->cmd[0][0] == '/')
		{
			error = execve(cmd->cmd[0], cmd->cmd, data->env);
			if (error == -1)
				ft_putstr_fd (RED"Error : comand no found\n"RESET, 2);
		}
		else
		{
		    dup2 (cmd->fd[1], 1); // escritura en el hijo
		 	close (cmd->fd[0]); //cierra lectura en el hijo
			i = -1;
			while (data->path[++i] != 0)
			{
				tmp = NULL;
				tmp = check_access(data->path[i], cmd->cmd[0]);
				error = execve(tmp, cmd->cmd, data->env);
			}
			if (error)
				ft_putendl_fd( RED"Error : comand no found"RESET, 2);
		}
		exit (EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &error, 0);
		//close (cmd->fd[1]); // close write father
		//dup2 (cmd->fd[0], 0); // read father
	}
  return (0);
}

int builtins(t_cmd *cmd, t_data *data)
{
  if (!ft_strncmp(cmd->cmd[0], "exit", ft_strlen(cmd->cmd[0])) && !cmd->cmd[1])
  {
	ft_exit(data);
	return (1);
  }
  return (0);
}
