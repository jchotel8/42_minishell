/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replaceenvignore.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:16:01 by jchotel           #+#    #+#             */
/*   Updated: 2019/11/09 14:24:07 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int        ft_lookupredir(char *ref/*, char **new*/)
{
  int fd;
	char *trimmed;

	trimmed = ft_strtrimignore(ref);
	fd = open(trimmed, O_RDONLY, S_IREAD | S_IWRITE);
	dup2(fd, 0);
  close(fd);
	return(0);
}

int        ft_isspaceredir(char c)  //a ajouter dans la libft
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f'
            || c == '\r');
}

int        ft_isendredir(char c)
{
    return (ft_isspaceredir(c) || !c /*|| c == '"' || c == '\'' */|| c == '<');
}


char        *ft_leftredirignore(char *s)
{
    int     j;
		int			i;
    int     k;
    char    current;
		char		temp;

    current = 0;
		i = 0;
    j = 0;
    k = 0;
    while (s[i])
    {
        switch_inside(&current, s[i]);
        if(s[i] == '<' && !current)
        {
						k = 0;
						s[i++] = ' ';
						while (ft_isspaceredir(s[i]))
							i++;
            while (!ft_isendredir(s[i + k]))
              k++;
						temp = s[i + k];
						s[i + k] = '\0';
            ft_lookupredir(s + i);
						s[(i = i + k)] = temp;
        }
        else
            s[j++] = s[i++];
    }
		s[j] = 0;
    return (s);
}
