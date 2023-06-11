/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:26:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/06/11 13:10:40 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*prompt(char **env)
{
	char	*prompt;
	char	*user;
	char	*host;

	user = ft_getenv_builtins("USER", env);
	if (!user)
		user = ft_strdup("Anonimo");
	user[0] = ft_toupper(user[0]);
	user = ft_strjoin("\033[1;31m", user, 0);
	anfitrion = ft_strjoin("\033[1;34m@MiniShell\033[0m", "🙂🚀❯  ", 0);
	prompt = ft_strjoin(user, host, 1);
	free (host);
	return (prompt);
}

void	*free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free (array);
	return (NULL);
}

void	print(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_printf ("[%s] ", str[i]);
	ft_printf ("\n");
}

int	search(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

int	err_msg(char *str)
{
	if (str)
		ft_putendl_fd(str, 2);
	return (1);
}
