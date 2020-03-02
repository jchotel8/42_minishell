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

int	ft_strcountignore(char *s)
{
	int		i;
	int		count;
	char	current;

	current = 0;
	count = 0;
	i = 0;
	while (s[i])
	{
		if (switch_inside(&current, s[i]))
			count++;
		i++;
	}
	return (count);
}
