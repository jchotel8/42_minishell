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

char		*ft_strtrimignore(char *s)
{
	int		i;
	int		j;
	int		inside;
	char	current;

	current = 0;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (switch_inside(&current, s[i], &inside))
			i++;
		s[j] = s[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}