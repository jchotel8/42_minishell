/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:31:43 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/05 19:56:41 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int				switch_inside(char *current, char new, char prev)
{
	if ((new == '\'' || new == '"') && !*current && prev != '\\')
	{
		*current = new;
		return (1);
	}
	else if ((new == '\'' || new == '"') && *current == new && ((*current == '\"' && prev != '\\') || (*current == '\'')))
	{
		*current = 0;
		return (1);
	}
	return (0);
}

static size_t	ft_countignore(char *s, char c, int i)
{
	size_t	count;
	char	*ptr;
	char	current;
    char    prev;

	ptr = (char*)s;
    prev = 0;
	current = 0;
	while (i == 1 && *s && *s == c)
		s++;
	if (*s)
		count = 1;
	else
		count = 0;
	while (*s)
	{
		switch_inside(&current, *s, prev);
		if (!current && *s == c && *(s + 1) && ((*(s + 1) != c && i == 1) || (i == 0)))
			count++;
        prev = *s;
		s++;
	}
	return (count);
}

char			**prep_ignore(char *s, char c, int i)
{
	char			**splitted;
	int				nb_words;

	if (!s)
		return (0);
	nb_words = ft_countignore((char *)s, c, i);
	if (!(splitted = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (0);
	return (splitted);
}

char			**ft_splitignore(char const *s, char c, int i)
{
	char	*ptr;			//posi of beginning of word
	char	**splitted;
	char	**start;
	char	current;		//is type " or '
    char    prev;

	current = 0;
    prev = 0;
	if (!(splitted = prep_ignore((char*)s, c, i)))
		return (0);
	ptr = (char*)s;
	start = splitted;
	while (*s)
	{
		switch_inside(&current, *s, prev);
		if (!current && *s == c)
		{
			if (ptr != s)
				*(splitted++) = ft_substr(ptr, 0, s - ptr);
			ptr = (char *)s + i;
		}
        prev = (char)s;
		s++;
	}
	if (ptr != s)
		*(splitted++) = ft_substr(ptr, 0, s - ptr);
	*splitted = 0;
	return (start);
}
