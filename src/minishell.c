/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/25 13:31:30 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
void get_env_and_path(t_data *data, char **env)
{
	int i;

	data->env = ft_calloc(arr_size(env) + 1, sizeof(char *));
	if (!data->env)
		err(RED"minishell: malloc error"RESET);
	i = -1;
	while (env[++i])
		data->env[i] = ft_strdup(env[i]);
	data->env[i] = NULL;
	data->path = ft_split(getenv("PATH"), ':', 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*user;
	
	if (ac > 1 && arr_size(av) > 1)
	  err("minishell: too many arguments");
	ft_bzero (&data, sizeof(t_data));
	user = prompt();
	data.exit = 1;
	while (data.exit)
	{
		signals();
		data.line = readline(user);
		if (!data.line)
			break;
		else if (lexer(&data, env))
			continue ;
		parser(&data);
	}
	free (user);
	free (data.path);
	free (data.env);
	exit(EXIT_SUCCESS);
}
