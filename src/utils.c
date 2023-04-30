/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:26:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/30 15:30:53 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*prompt(void)
{
	char	*prompt;
	char	*user;
	char	*anfitrion;

	user = getenv("USER");
	if (!user)
		user = ft_strdup("\033[1;31mAnonimo\033[0m");
	user[0] = ft_toupper(user[0]);
	user = ft_strjoin("\033[1;31m", user, 0);
	anfitrion = ft_strjoin("\033[1;34m@MiniShell\033[0m", "🚀> ", 0);
	prompt = ft_strjoin(user, anfitrion, 0);
	free(user);
	free (anfitrion);
	return (prompt);
}

void	*free_array(char **array)
{
	int i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free (array);
  return (NULL);
}

void print(char **str)
{
  int i;

  i	= -1;
  while (str[++i])
	printf ("[%s] ", str[i]);
}

int	search(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}
