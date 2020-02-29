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

#include "../../includes/minishell.h"

int				switch_inside(char *current, char new, int *inside)
{
	if ((new == '\'' || new == '"') && !*current)
	{
		*inside = 1;
		*current = new;
		return (1);
	}
	else if ((new == '\'' || new == '"') && *current == new)
	{
		*inside = 0;
		*current = 0;
		return (1);
	}
	return (0);
}

static size_t	ft_countignore(char *s, char c, int i)
{
	size_t	count;
	char	*ptr;
	int		inside;
	char	current;

	ptr = (char*)s;
	current = 0;
	inside = 0;
	while (i == 1 && *s && *s == c)
		s++;
	if (*s)
		count = 1;
	else
		count = 0;
	while (*s)
	{
		switch_inside(&current, *s, &inside);
		if (!inside && *s == c && *(s + 1) && ((*(s + 1) != c && i == 1) || (i == 0)))
			count++;
		s++;
	}
	return (count);
}

char			**prep_ignore(int *inside, char *s, char c, int i)
{
	char			**splitted;
	int				nb_words;

	*inside = 0;
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
	int		inside;			//is inside
	char	current;		//is type " or '

	current = 0;
	if (!(splitted = prep_ignore(&inside, (char*)s, c, i)))
		return (0);
	ptr = (char*)s;
	start = splitted;
	while (*s)
	{
		switch_inside(&current, *s, &inside);
		if (!inside && *s == c)
		{
			if (ptr != s)
				*(splitted++) = ft_substr(ptr, 0, s - ptr);
			ptr = (char *)s + i;
		}
		s++;
	}
	if (ptr != s)
		*(splitted++) = ft_substr(ptr, 0, s - ptr);
	*splitted = 0;
	return (start);
}
