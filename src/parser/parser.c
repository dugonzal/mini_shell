/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 21:15:13 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/06/10 14:54:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parser_cmds(char **bufer, t_cmd **cmd)
{
	int	size;

	size = size_node(bufer);
	last_back_node(cmd, new_node(bufer, size));
	return (size);
}

void	copy_fd(t_data *data)
{
	int	fd;

	fd = dup(0);
	if (fd < 0)
		error_fd(data);
	data->fd[0] = fd;
	fd = dup(1);
	if (fd < 0)
		error_fd(data);
	data->fd[1] = fd;
}

void	reset_fd(t_data *data)
{
	if (dup2(data->fd[0], 0) < 0)
	{
		perror(RED"dup2: "RESET);
		data->status = 1;
		close(data->fd[0]);
		close(data->fd[1]);
		return ;
	}
	close (data->fd[0]);
	if (dup2(data->fd[1], 1) < 0)
	{
		perror(RED"dup2: "RESET);
		data->status = 1;
		close(data->fd[0]);
		return ;
	}
	close (data->fd[1]);
}

int	exec(t_cmd *cmd, t_data *data)
{
	t_cmd	*tmp;

	tmp = cmd;
	copy_fd(data);
	while (tmp)
	{
		if (tmp->type == 5)
			if (pipe(tmp->pipe) < 0)
				return (err_msg(RED"Error : pipe"RESET));
	//	redir (cmd);
		search_quotes(tmp, "\"\'");
		if (builtins_2(tmp, data))
			;
		else
		{
			bin_execute(tmp, data);
			data->status = cmd->status;
		}
		if (tmp->type != 5)
			reset_fd(data);
		else if (tmp->type == 5)
			ft_dup2(tmp->pipe, 0);
		tmp = tmp->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	ft_bzero (&cmd, sizeof(cmd));
	while (data->bufer[i])
	{
		if (search("|;", data->bufer[i][0]))
			i++;
		else if (data->bufer[i])
			i += parser_cmds(&data->bufer[i], &cmd);
	}
	free (data->bufer);
	if (cmd)
		exec(cmd, data);
	free_cmd(cmd);
	return (0);
}
