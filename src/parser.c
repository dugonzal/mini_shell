/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/10 12:32:39 by ciclo            ###   ########.fr       */
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
	i = -1;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(bin) + 2));
	if (!tmp)
		return (NULL);
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

void	bin_execute(t_data *mini)
{
	int		error;
	int		i;
	char	*tmp;

	error = 0;
	tmp = NULL;
	mini->pid = fork();
	if (!ft_strncmp(mini->line, "exit", 4))
	{
		mini->status = 0;
		return ;
	}
	if (!mini->pid)
	{
		if (mini->bufer[0][0] == '.' || mini->bufer[0][0] == '/')
		{
			error = execve(mini->bufer[0], mini->bufer, mini->env);
			if (error == -1)
				printf  (RED"Error : comando no funciona\n"RESET);
		}
		else
		{
			i = -1;
			while (mini->path[++i] != 0)
			{
				tmp = check_access(mini->path[i], mini->bufer[0]);
				error = execve(tmp, mini->bufer, mini->env);
				free (tmp);
			}
			if (error != 0)
				printf  (RED"Error : comando no funciona\n"RESET);
		}
		exit (EXIT_SUCCESS);
	}
	else
		wait(NULL);
	return ;
}


// voy a quitar las comilla y comprobar que hayan dos
//No interpretar comillas sin cerrar o caracteres especiales no especificados en el
//enunciado como \ (barra invertida) o ; (punto y coma).
// voy hacer primero el caso en el que los caracteres entre comillas no tienen
// espacios luego con espacios
int	verify_quotes(t_data *data)
{
	int i;
	int	err[2];

	err[1] = 0;
	err[0] = 0;
	i = 0;
	while (data->line[i] != 0)
	{
		if (data->line[i] == '"')
			err[0]++;
		else if (data->line[i] == '\'')
			err[1]++;
		i++;
	}
	if (err[1] % 2 != 0 || err[0] % 2 != 0)
	{
		printf (RED"Error : comillas sin cerrar\n"RESET);
		return (1);
	}
	return (0);
}

void	parser(t_data *data)
{
	if (verify_quotes(data))
		return;
	data->bufer = ft_split(data->line, ' ');
	bin_execute(data);
}
