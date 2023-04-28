/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dugonzal <dugonzal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/04/28 23:10:06 by dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//analizar los tokens y divida aquellos que se unieron. Podrías verificar\
//si hay caracteres de redirección o tuberías entre dos tokens, y si los hay, dividir el token en dos.
int check_pipe(char **str, char c)
{
  int i;

  i = 0;
  while (str[i])
  {
	if (str[arr_size(str) - 1][0] == c \
	||	(ft_strlen(str[i]) > 1 && str[i][0] == c && str[i][1] == c) || !ft_strncmp(str[i], "||", 2))
	{
	  ft_putstr_fd(RED"minishell: syntax error near unexpected token `|'\n"RESET, 2);
	  return (2);
	}
	else if (ft_strlen(str[i]) == 1 && !ft_strncmp(str[i],&c, 1))
	  return (1);
	else
	  i++;
  }
  return (0);
}

int check_redir(char **str, char c)
{
  int i;

  (void)c;
  i = 0;
  while (str[i]) // str[i] = ">" || "<" || "> + >" || "< + <"
  {
	if (str[arr_size(str) - 1][0] == c)
	{
	  ft_putstr_fd(RED"minishell: syntax error  `< >'\n"RESET, 2);
	  return (2);
	}
	i++;
  }
  return (0);
}

/// si se ponen los carac
int	lexer(t_data *data)
{
  if (data->line[0] == '\0' || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  if (!(data->bufer = split_token(data->line, " \t\v\f\r")))
  	return (1);
  // antes de analizar tengo que recorrer el array en busca de los caracteres especiales que esten juntos a un token
 // data->pipe = check_pipe(data->bufer, '|');
 // data->redir = check_redir(data->bufer, '>');
 // parse_tokens(data->bufer);
  //if (data->pipe == 2)
//	return (1);
  print (data->bufer);
  add_history (data->line);
 // free (data->line);
  return (0);
}


