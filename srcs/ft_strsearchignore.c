/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:16:01 by jchotel           #+#    #+#             */
/*   Updated: 2019/11/09 14:24:07 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_lookup(t_shell *sh, char *s, char **s2, int len)
{
	t_list	*tmp;
	int		pad;

	tmp = sh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, s, len))
		{
				*s2 = ft_strjoin(*s2, ((char*)tmp->content) + len + 1);
				pad = ft_strlen(*s2);
				*s2 = ft_strjoin(*s2, s);
				(*s2)[pad] = '\0';
				// ft_printf("%d\n",ft_strlen(((char*)tmp->content) + len + 1));
				return (ft_strlen(((char*)tmp->content) + len + 1));
		}
		tmp = tmp->next;
	}
	return (0);
}

int		ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f'
		|| c == '\r');
}

int		ft_isend(char c)
{
	return (ft_isspace(c) || !c || c == '"' || c == '\'' || c == '$');
}


char		*ft_strsearchignore(t_shell *sh, char *s)
{
	int		j;
	int		k;
	char	current;
	char	*s2;

	s2 = ft_calloc(ft_strlen(s), sizeof(char));
	current = 0;
	j = 0;
	k = 0;
	while (*s)
	{
		switch_inside(&current, *s);
		if(*s == '$' && current != '\'')
		{
			s++;
			while (!ft_isend(*(s+k)))
				k++;
			j += ft_lookup(sh, s, &s2, k);
			s += k;
			k = 0;
		}
		else
			s2[j++] = *((s++)+k);
	}
	return (s2);
}
