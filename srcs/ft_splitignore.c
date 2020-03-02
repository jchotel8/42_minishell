/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:31:43 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 02:15:34 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				switch_inside(char *current, char new)
{
	if ((new == '\'' || new == '"') && !*current)
	{
		*current = new;
		return (1);
	}
	else if ((new == '\'' || new == '"') && *current == new)
	{
		*current = 0;
		return (1);
	}
	return (0);
}

static size_t	ft_countignore(char *s, char c)
{
	size_t	count;
	char	*ptr;
	char	current;

	ptr = (char*)s;
	current = 0;
	while (*s && *s == c)
		s++;
	if (*s)
		count = 1;
	else
		count = 0;
	while (*s)
	{
		switch_inside(&current, *s);
		if (!current && *s == c && *(s + 1) && *(s + 1) != c)
			count++;
		s++;
	}
	return (count);
}

char			**prep_ignore(char *s, size_t *nb_words, char c)
{
	char			**splitted;

	if (!s)
		return (0);
	*nb_words = ft_countignore((char *)s, c);
	if (!(splitted = (char **)malloc(sizeof(char *) * (*nb_words + 1))))
		return (0);
	return (splitted);
}

char			**ft_splitignore(char const *s, char c)
{
	size_t	nbwords;
	char	*ptr;
	char	**splitted;
	char	current;

	current = 0;
	if (!(splitted = prep_ignore((char*)s, &nbwords, c)))
		return (0);
	ptr = (char*)s;
	while (*s)
	{
		switch_inside(&current, *s);
		if (!current && *s == c)
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
