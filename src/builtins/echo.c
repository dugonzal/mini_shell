/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:42:28 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/09 19:47:00 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


int ft_echo(char **str)
{
  int i;
  int flag;

  i = -1;
  flag = 0;
  while (str[++i])
  {
	if (!ft_strncmp(str[i], "-n", 2))
	{
	  flag = 1;
	  continue ;
	}
	ft_printf ("%s", str[i]);
  }
  if (!flag)
	  printf ("\n");
  return (0);
} 

