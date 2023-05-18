/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/18 10:39:22 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
void get_env(t_data *data, char **env)
{
  int i;

  i = -1;
  data->env = ft_calloc(arr_size(env) + 1, sizeof(char *));
  if (!data->env)
		err(RED"minishell: malloc error"RESET);
  while (env[++i])
		data->env[i] = ft_strdup(env[i]);
  data->env[i] = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*user;
	
	if (ac > 1 && arr_size(av) > 1)
	  err("minishell: too many arguments");
	ft_bzero (&data, sizeof(t_data));
	data.path = ft_split(getenv("PATH"), ':', 0);
	user = prompt();
	get_env(&data, env);
	while (42)
	{
		signals();
		data.line = readline (user);
		if (!data.line)
			break;
		if (lexer(&data))
			continue ;
		parser(&data);
	}
	free (user);
	free (data.path);
	free (data.env);
	exit(EXIT_SUCCESS);
}
