/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/06 18:08:02 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
void	get_env_and_path(t_data *data, char **env)
{
	int		i;

	data->env = ft_calloc(arr_size(env) + 1, sizeof(char *));
	if (!data->env)
		err(RED"minishell: malloc error"RESET);
	i = -1;
	while (env[++i])
	{
		data->env[i] = ft_strdup(env[i]);
		if (!data->env[i])
			err(RED"minishell: malloc error"RESET);
	}
	data->env[i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1 && arr_size(av) > 1)
		err(RED"minishell: too many arguments"RESET);
	ft_bzero (&data, sizeof(t_data));
	get_env_and_path(&data, env);
	data.user = prompt();
	while (42)
	{
		signals();
		data.line = readline(data.user);
		if (data.line && *data.line)
		{
			add_history(data.line);
		printf ("line: %s\n", data.line);
		}
		if (!data.line)
			break ;
		else if (lexer(&data))
			continue ;
		parser(&data);
		data.path = ft_split(ft_getenv_builtins("PATH", data.env), ':', 0);
	}
	return (0);
}
