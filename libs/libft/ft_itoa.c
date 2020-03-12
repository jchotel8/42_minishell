/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 16:58:42 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/12 01:43:23 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_itoa(int i)
{
	long	n;
	int		c;
	char	*s;

	c = i < 0;
	n = c ? -(long)i : i;
	while (i /= 10)
		c++;
	s = ft_calloc(c + 1, 1);
	*s = '-';
	while ((s[c] = n % 10 + '0') && (n /= 10))
		c--;
	return (s);
}
