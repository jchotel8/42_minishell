/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replaceenvignore.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:16:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/12 01:54:45 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*prolong(char *src, char *ref)
{
	char	*new;
	int		len_1;
	int		len_2;

	len_1 = ft_strlen(src);
	len_2 = ft_strlen(ref);
	new = ft_calloc(len_1 + len_2 + 1, sizeof(char));
	ft_memcpy(new, src, len_1);
	free(src);

	return (new);
}

int		ft_questionmark(t_shell *sh, char *ref, char **new)
{
	char	*tmp_str;
	char	*nbstr;

	nbstr = ft_itoa(sh->ret);
	tmp_str = *new;
	*new = ft_strjoin(*new, nbstr);
	free(tmp_str);
	*new = prolong(*new, ref);
	return (ft_strlen(nbstr));
}

int        ft_lookup(t_shell *sh, char *ref, char **new, int len)
{
    t_list    *tmp;
    char       *tmp_str;

    tmp = sh->env;
    while (tmp)
    {
        if (!ft_strncmp(tmp->content, ref, len) && ((char*)tmp->content)[len] == '=')
        {
            tmp_str = *new;
            *new = ft_strjoin(*new, ((char*)tmp->content) + len + 1);
            free(tmp_str);
            *new = prolong(*new, ref);
            return (ft_strlen(((char*)tmp->content) + len + 1));
        }
        tmp = tmp->next;
    }
    return (0);
}

int        ft_isspace(char c)  //a ajouter dans la libft
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f'
            || c == '\r');
}

int        ft_isend(char c)
{
    return (ft_isspace(c) || !c || c == '"' || c == '\'' || c == '$');
}


char		*ft_replaceenvignore(t_shell *sh, char *s)
{
	int		j;
	int		k;
	char	current;
	char	*new;
	char	prev;

	new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	current = 0;
	j = 0;
	k = 0;
	prev = 0;
	while (*s)
	{
		switch_inside(&current, *s, prev);
		prev = *s;
		if(*s == '$' && current != '\'')
		{
						k = 0;
			s++;
			if(*s == '?')
				j += ft_questionmark(sh, s++, &new);
			else
			{
				while (!ft_isend(*(s + k)))
					k++;
				j += ft_lookup(sh, s, &new, k);
				s += k;
			}
		}
		else
			new[j++] = *((s++));
	}
	new[j] = 0;
	return (new);
}
