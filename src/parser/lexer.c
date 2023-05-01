/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:58:25 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/01 22:36:02 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//analizar los tokens y divida aquellos que se unieron. Podrías verificar\
//si hay caracteres de redirección o tuberías entre dos tokens, y si los hay, dividir el token en dos.

// 1. comprobar que las comillas estan cerradas
// 2. comprobar que los caracteres especiales estan bien
int check_quotes(char **prompt, char *quotes)
{
  int	i;
  int	j;
  char	tmp_quote;

  i = -1;
  while (prompt[++i])
  {
	  j = 0;
	  if (prompt[i] && search(quotes, prompt[i][j]))
	  {
		tmp_quote = prompt[i][j];
		while (prompt[i][++j] != tmp_quote)
		  if (prompt[i][j] == '\0')
		  	return (1);
	  }
  }
  return (0);
}

int	check_pipe(char **prompt, char specials)
{
  int size;
  
  size = arr_size(prompt);
  if (prompt[size - 1][0] == specials)
	return (1);
  else if ((!(arr_size(prompt) > 1) && prompt[0][0] == specials))
	return (1);
  return (0);
}

int	lexer(t_data *data)
{
  if (data->line[0] == '\0' || !ft_strlen(data->line))
	return (1);
  data->line = ft_strtrim(data->line, " \t\v\f\r", 1);
  data->bufer = split_token(data->line, " \t\v\f\r", ">|<", "\"\'");
  if (!data->bufer)
	  return (1);
  if (check_quotes(data->bufer, "\'\"") || check_pipe(data->bufer, '|'))
  {
    ft_putstr_fd (RED"sintax error minishell\n"RESET, 2);
    free_array (data->bufer);
    return (1);
  }
  if (!ft_strncmp(data->bufer[0], "exit", 4) && ft_strlen(data->bufer[0]) == 4 \
	&& !data->bufer[1])
  {
      ft_exit (data);
	  return (1);
  }
  print (data->bufer);
	// prin (data->bufer);
  // antes de analizar tengo que recorrer el array en busca de los caracteres especiales que esten juntos a un token
 // data->redir = check_redir(data->bufer, '>');
 // parse_tokens(data->bufer);
  //if (data->pipe == 2)
//	return (1);
  //print (data->bufer);
  add_history (data->line);
  free (data->line);
  return (0);
}


