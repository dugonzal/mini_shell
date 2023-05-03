/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:48:17 by Dugonzal          #+#    #+#             */
/*   Updated: 2023/05/03 15:12:42 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		  if (prompt[i][j] == 0)
		  	return (1);
	  }
  }
  return (0);
}

int	check_pipe(char **prompt, char pipe)
{
  int size;
  int i;

  size = arr_size(prompt);
  if (prompt[0][0] == pipe || prompt[size - 1][0] == pipe)
	return (1);
  i = -1;
  while (++i < (size - 1))
	if (prompt[i] && prompt[i][0] == pipe && prompt[i][1] == pipe)
	  return (1);
  return (0);
}

int check_redir(char **prompt, char redir)
{
  int i;
  int size;

  size = arr_size(prompt);
  if (prompt[0] && prompt[size - 1][0] == redir)
	return (1);
  i = -1;
  while (prompt[++i])
	if (prompt[i] && prompt[i][0] == redir && prompt[i][2] == redir)
	  return (1);
	else if (prompt[i] && prompt[i][0] == redir &&  search(">|<", prompt[i + 1][0]))
	  return (1);
  return (0);
}












