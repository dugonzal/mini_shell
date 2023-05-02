/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:48:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/02 15:35:04 by Dugonzal         ###   ########.fr       */
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
void	bin_execute(t_data *mini)
{
	int		error;
	int		i;
	char	*tmp;

	error = 0;
	mini->pid = fork();
	if (!mini->pid)
	{
		if (mini->bufer[0][0] == '.' || mini->bufer[0][0] == '/')
		{
			error = execve(mini->bufer[0], mini->bufer, mini->env);
			if (error == -1)
				printf  (RED"Error : comand no found\n"RESET);
		}
		else
		{
			i = -1;
			while (mini->path[++i] != 0)
			{
				tmp = NULL;
				tmp = check_access(mini->path[i], mini->bufer[0]);
				error = execve(tmp, mini->bufer, mini->env);
			}
			if (error)
				ft_putstr_fd( RED"Error : comand no found\n"RESET, 2);
		}
		exit (EXIT_SUCCESS);
	}
	else
		wait(NULL);
}
