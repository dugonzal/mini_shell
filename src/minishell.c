/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/08 22:05:23 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Buscar y ejecutar el ejecutable correcto basado en
 la variable PATH o mediante el
uso de rutas relativas o absolutas)
 Ejecutar el comando con sus argumentos
 Esperar a que el comando termine su ejecución
 Mostrar el prompt de nuevo
 voy a empezar por buscar el ejecutable en el PATH*/
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
	if (!access(tmp, F_OK))
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
	i = -1;
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
				perror ("Error :");
		}
		else
			while (mini->path[++i] != 0)
			{
				tmp = check_access(mini->path[i], mini->bufer[0]);
				error = execve(tmp, mini->bufer, mini->env);
			}
			if (error != 0)
				perror ("Error :");
		free (tmp);
		exit (1);
	}
	else
		wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	*mini;

	(void)av;
	(void)ac;
	mini = (t_data *)malloc(sizeof(t_data));
	if (!mini)
		exit(EXIT_FAILURE);
	ft_memset (mini, 0, sizeof(t_data));
	mini->status = 1;
	mini->path = ft_split(getenv("PATH"), ':');
	while (mini->status)
	{
		signals();
		mini->line = readline (BLUE"minishell$GUEST$> "RESET);
		add_history (mini->line);
		mini->bufer = ft_split(mini->line, ' ');
		mini->env = env;
		bin_execute(mini);
		free (mini->line);
		free (mini->bufer);
	}
	free (mini);
	exit(EXIT_SUCCESS);
}
