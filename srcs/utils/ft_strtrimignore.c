/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:16:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/06 10:49:40 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		*ft_strtrimignore(char *s)
{
	int		i;
	int		j;
	char	current;
	int		inside;
    char	prev;

	current = 0;
	inside = 0;
    prev = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
        if (switch_inside(&current, s[i], prev))
        {
        	prev = s[i];
            i++;
            inside = (inside == 0 ? 1 : 0);
        }
        if ((s[i] == '\\' && prev != '\\' && !current) || (current == '"' && (s[i + 1] == '\\' || s[i + 1] == '"') && s[i] == '\\'))
		{
        	prev = s[i];
        	i++;
		}
        else
        {
            s[j] = s[i];
            prev = s[i];
            i++;
            j++;
        }
	}
	s[j] = '\0';
	return (s);
}
