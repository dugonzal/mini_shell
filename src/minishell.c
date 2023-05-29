/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/29 15:52:04 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
void get_env_and_path(t_data *data, char **env)
{
	int i;
	char *path;

	data->env = ft_calloc(arr_size(env) + 1, sizeof(char *));
	if (!data->env)
		err(RED"minishell: malloc error"RESET);
	i = -1;
	while (env[++i])
		data->env[i] = ft_strdup(env[i]);
	data->env[i] = NULL;
	path = getenv("PATH");
	data->path = ft_split(path, ':', 0);

}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	
	if (ac > 1 && arr_size(av) > 1)
	  err("minishell: too many arguments");
	ft_bzero (&data, sizeof(t_data));
	data.user = prompt();
	while (42)
	{
		signals();
		data.line = readline(data.user);
		if (!data.line)
			break;
		else if (lexer(&data, env))
			continue ;
		parser(&data);
	}
	return (0);
}
