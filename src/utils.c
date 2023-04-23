/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 21:26:30 by ciclo             #+#    #+#             */
/*   Updated: 2023/04/22 19:08:33 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*prompt(void)
{
	char	*prompt;
	char	*user;
	char	*anfitrion;

	if (!(user = getenv("USER")))
		user = ft_strdup("\033[1;31mAnonimo\033[0m");
	user[0] = ft_toupper(user[0]);
	user = ft_strjoin("\033[1;31m", user, 0);
	anfitrion = ft_strjoin("\033[1;34m@MiniShell\033[0m", "🚀> ", 0);
	prompt = ft_strjoin(user, anfitrion, 0);
	free(user);
	free (anfitrion);
	return (prompt);
}
     


void print(char **str)
{
  int i;

  i	= 0;
  while (str[i])
  {
	printf ("[%s] ", str[i]);
	i++;
  }
}

