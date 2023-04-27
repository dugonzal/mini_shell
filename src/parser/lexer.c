/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/27 13:14:03 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int check_pipe(char **str, char c)
{
  int i;

  i = 0;
  while (str[i])
  {
	if (ft_strlen(str[i]) > 1 && str[i][0] == c && str[i][1] == c)
	{
	  ft_putstr_fd(RED"minishell: syntax error near unexpected token `|'\n"RESET, 2);
	  return (1);
	}
	else if (ft_strlen(str[i]) == 1 && str[i][0] == c)
	  return (2);
	else
	  i++;
  }
  return (0);
}

//int check_redir(char *str, char c)

int	lexer(t_data *data)
{
  if (data->line[0] == '\0' || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  if (!(data->bufer = split_token(data->line, " \t\v\f\r")))
  	return (1);
  data->pipe = check_pipe(data->bufer, '|');

  print (data->bufer);
  add_history (data->line);
  free (data->line);
  return (0);
}


