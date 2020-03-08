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

char    *prolongredir(char *src, char *ref)
{
    char    *new;
    int     len_1;
    int     len_2;

    len_1 = ft_strlen(src);
    len_2 = ft_strlen(ref);
    new = ft_calloc(len_1 + len_2 + 1, sizeof(char));
    ft_memcpy(new, src, len_1);
    free(src);

    return (new);
}

int        ft_lookupredir(char *ref/*, char **new*/)
{
	// char *line;
	// char *oldnew = *new;
	// char *tmp_str;

  int fd = open(ref, O_CREAT | O_RDWR, S_IREAD | S_IWRITE);
	// int old_stdio =
	dup(0);
	dup2(fd, 0);

    close(fd);
	// while (get_next_line(fd,&line))
	// {
	// 	tmp_str = *new;
	// 	*new = ft_strjoin(*new, line);
  //   free(tmp_str);
	// }
  // *new = prolongredir(*new, ref);
	// close(fd);
  // return (ft_strlen(*new) - ft_strlen(oldnew));
	return(0);
}

int        ft_isspaceredir(char c)  //a ajouter dans la libft
{
    return (c == ' ' || c == '\t' || c == '\v' || c == '\n' || c == '\f'
            || c == '\r');
}

int        ft_isendredir(char c)
{
    return (ft_isspaceredir(c) || !c || c == '"' || c == '\'' || c == '<');
}


char        *ft_leftredirignore(char *s)
{
    int     j;
    int     k;
    char    current;
    char    *new;

    new = ft_calloc(ft_strlen(s) + 1, sizeof(char));
    current = 0;
    j = 0;
    k = 0;
    while (*s)
    {
        switch_inside(&current, *s);
        if(*s == '<' && current != '\'')
        {
						k = 0;
						*s = ' ';
            s++;
						while (ft_isspaceredir(*(s + k)))
                k++;
            while (!ft_isendredir(*(s + k)))
                k++;
						char temp = *(s + k);
						*(s + k) = '\0';
            ft_lookupredir(s/*, &new*/);
						*(s + k) = temp;
            s += k;
        }
        else
            new[j++] = *((s++));
    }
		new[j] = 0;
		ft_printf("[%s]\n", new);
    return (new);
}
