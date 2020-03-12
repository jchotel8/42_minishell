/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:53 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/11 19:16:13 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_echo(t_shell *sh)
{
	int		i;
	int		flag_n;

	i = 0;
	flag_n = 0;
	if (sh->arg && !ft_strcmp("-n", sh->arg[i]))
	{
		i++;
		flag_n = 1;
	}
	while (sh->arg && sh->arg[i])
	{
		i >= 1 ? ft_printf(" ") : 0;
		if (!ft_strcmp(sh->arg[i], "$?"))
			ft_printf("sh->ret : %d", sh->ret);
		else
			ft_printf("%s", sh->arg[i]);
		i++;
	}
	if (!flag_n)
		ft_printf("\n");
}
