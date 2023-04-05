/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciclo <ciclo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/05 17:52:43 by ciclo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Buscar y ejecutar el ejecutable correcto (basado en
// la variable PATH o mediante el
//uso de rutas relativas o absolutas)
// Ejecutar el comando con sus argumentos
// Esperar a que el comando termine su ejecución
// Mostrar el prompt de nuevo

// voy a empezar por buscar el ejecutable en el PATH

char *get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_strdup(env[i] + 5);
			if (!path)
				exit(EXIT_FAILURE);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	execute_comand(t_data *data, char **env)
{
	pid_t	pid;
	int		error;
	char *path;

	(void)env;
	error = 0;
	pid = fork();
	if (pid != 0)
		perror ("Error");
	path = get_path(env);
	if (pid == 0)
	{
		printf ("data->bufer[0] = %s", data->bufer[0]);
		error = execve("/bin/ls", data->bufer, &path);
		if (error == -1)
			perror ("Error");
	}
	else
		wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	t_data	*mini;
	int		status;

	(void)av;
	(void)ac;
	(void)env;
	mini = (t_data *)malloc(sizeof(t_data));
	if (!mini)
		exit(EXIT_FAILURE);
	ft_memset (mini, 0, sizeof(t_data));
	status = 1;
	while (status)
	{
		mini->line = readline (BLUE"minishell$GUEST$> "RESET);
		add_history (mini->line);
		mini->env = env;
		mini->bufer = ft_split(mini->line, ' ');
		if (!ft_strncmp(mini->line, "exit", 4))
			status = 0;
		execute_comand(mini, env);
		free (mini->line);
	}
	return (0);
}
