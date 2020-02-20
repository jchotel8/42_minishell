/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:31:43 by jchotel           #+#    #+#             */
/*   Updated: 2019/11/09 14:22:04 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static size_t	ft_countignore(char *s, char c)
{
	size_t	count;
	size_t	i;
	int			inside;

	i = 0;
	inside = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		count = 1;
	else
		count = 0;
	while (s[i])
	{
		if (s[i] == '"')
			inside = 1 - inside;
		else if (!inside && s[i] == c && s[i + 1] && s[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

char				**prep_ignore(int *inside, char *s, size_t *nb_words, char c)
{
	char			**splitted;

	*inside = 0;
	if (!s)
		return (0);
	*nb_words = ft_countignore((char *)s, c);
	if (!(splitted = (char **)malloc(sizeof(char *) * (*nb_words + 1))))
		return (0);
	return (splitted);
}

char			**ft_splitignore(char const *s, char c)
{
	size_t			nbwords;
	char			*ptr;
	char			**splitted;
	int					inside;

	if (!(splitted = prep_ignore(&inside, (char*)s, &nbwords, c)))
		return (0);
	ptr = (char*)s;
	while (*s)
	{
		inside = (*s == '"' ? 1 - inside : inside);
		if (!inside && *s == c)
		{
			if (ptr != s)
				*(splitted++) = ft_substr(ptr, 0, s - ptr);
			ptr = (char *)s + 1;
		}
		s++;
	}
	if (ptr != s)
		*(splitted++) = ft_substr(ptr, 0, s - ptr);
	*splitted = 0;
	return (splitted - nbwords);
}
