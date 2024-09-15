/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:01:34 by ciclo             #+#    #+#             */
/*   Updated: 2024/09/15 12:44:43 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_status;

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac > 1 && arr_size(av) > 1)
		err(RED"minishell: too many arguments"RESET);
	ft_bzero (&data, sizeof(t_data));
	get_env_and_path(&data, env);
	g_status = 0;
	while (42)
	{
		signals();
		data.path = ft_split(ft_getenv_builtins("PATH", data.env), ':', 0);
		data.line = readline(prompt(data.env));
		if (!data.line)
			break ;
		else if (lexer(&data))
			continue ;
		parser(&data);
	}
	return (0);
}
