/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 09:03:08 by ciclo             #+#    #+#             */
/*   Updated: 2023/05/26 22:50:18 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_token(const char *prompt, char *set, char *specials, char *quotes)
{
	char	**tmp;
	int		word;

	tmp = (char **)ft_calloc((count_tokens(prompt, set, \
	quotes, specials) + 1), sizeof(char *));
	if (!tmp)
		return (NULL);
	word = 0;
	while (*prompt)
	{
		if (*prompt && search(specials, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, specials_token(prompt)));
		else if (*prompt && !search(specials, *prompt)
			&& !search(quotes, *prompt) && !search(set, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, \
			caracteres_token(prompt, set, quotes, specials)));
		else if (*prompt && search(quotes, *prompt))
			tmp[word++] = fun_check(ft_strndup(prompt, \
			quotes_token(prompt, *prompt, set)));
		prompt += ft_strlen(tmp[word - 1]);
		while (*prompt && search(set, *prompt))
			prompt++;
	}
	tmp[word] = NULL;
	return (tmp);
}
