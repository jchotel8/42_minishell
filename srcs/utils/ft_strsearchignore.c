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

#include "../../includes/minishell.h"

char *prolong(char *s2, char *s)
{
	char *s3;
	int	lens2;
	int	lens;

	lens2 = ft_strlen(s2);
	lens = ft_strlen(s);
	s3 = calloc(lens2 + lens, sizeof(char));
	memcpy(s3, s2, lens2);
	free(s2);

	return (s3);
}

int		ft_lookup(t_shell *sh, char *s, char **s2, int len)
{
	t_list	*tmp;

	tmp = sh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, s, len))
		{
				*s2 = ft_strjoin(*s2, ((char*)tmp->content) + len + 1);
				*s2 = prolong(*s2, s);
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
