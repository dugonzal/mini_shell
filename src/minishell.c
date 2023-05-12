/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/12 11:45:24 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// quotes = "\"\'"
// whitespaces = " \t\v\f\r\n"
// lexer -> parser -> expanser -> builtins -> bin_execute -> waitpid
//
int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*user;

	if (ac > 1 && arr_size(av) > 1)
	  err("minishell: too many arguments");
	ft_bzero (&data, sizeof(t_data));
	data.path = ft_split(getenv("PATH"), ':', 0);
	user = prompt();
	while (42)
	{
		signals();
		data.line = readline (user);
		if (!data.line)
			break ;
		data.env = env;
		if (lexer(&data))
			continue ;
		parser(&data);
	}
	free (user);
	free (data.path);
	exit(EXIT_SUCCESS);
}
