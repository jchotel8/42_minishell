/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:31:57 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/printf.h"

void	handle_s(char *buffer, t_arg *arg, int *count, int i)
{
	if (arg->flag != '-')
		padding((arg->flag == '0' ? '0' : ' '), arg->w1 -
		((arg->w2 < i && (arg->w2 > 0 || arg->precision == '.')
		&& arg->w2 >= 0) ? arg->w2 : i), count);
	if (!(arg->precision == '.' && arg->w2 == 0))
		ft_putstr_count(buffer, count, (i < arg->w2 && arg->precision
		== '.') ? i : arg->w2);
	if (arg->flag == '-')
		padding(' ', arg->w1 - ((arg->w2 < i && arg->w2 >= 0 &&
		arg->precision == '.') ? arg->w2 : i), count);
}
