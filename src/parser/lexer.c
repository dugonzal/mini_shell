/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/02 13:14:36 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int lexer_errors(t_data *data)
{
  if (check_quotes(data->bufer, "\'\""))
	return(err_msg(RED"minishell: syntax error quotes \" <-> \'  \n"RESET));
  else if (check_pipe(data->bufer, '|'))
	return(err_msg(RED"minishell: syntax error pipe '|'\n"RESET));
  else if (check_redir_output(data->bufer, '<'))
	return (err_msg(RED"minishell: syntax error redir '<'\n"RESET));
  else if (check_redir_output(data->bufer, '>'))
	return (err_msg(RED"minishell: syntax error redir '>'\n"RESET));
  return (0);
}

void	expanser(t_data *data)
{
  int i;
  int j;

  j = 0;
  i = -1;
  while (data->env[++i])
  {
	j = -1;
	while (data->env[i][++j])
	  if (data->env[i][j] == '$')
		printf ("[$\n");
  }
}

int	lexer(t_data *data)
{
  if (data->line[0] == '\0' || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  data->bufer = split_token(data->line, " \t\v\f\r", ">|<", "\"\'");
  if (!data->bufer)
	  return (1);
  else if (lexer_errors(data))
	return (1);
  expanser(data);
  print (data->bufer);
  add_history (data->line);
  free (data->line);
  return (0);
}


