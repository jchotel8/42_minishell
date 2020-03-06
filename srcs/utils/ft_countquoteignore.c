/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 22:16:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/05 19:56:41 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_countquoteignore(char *s)
{
	int		i;
	int		count;
	char	current;
    char    prev;

    prev = 0;
	current = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (switch_inside(&current, s[i], prev))
			count++;
        prev = s[i];
		i++;
	}
	return (count);
}
