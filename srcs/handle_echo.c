/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:53 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_echo(t_shell *sh)
{
	int		i;
	int		flag_n;
	char	*tmp;

	i = 0;
	flag_n = 0;
	if (!ft_strcmp("-n", sh->arg[i]))
	{
		i++;
		flag_n = 1;
	}
	while (sh->arg && sh->arg[i])
	{
		tmp = sh->arg[i];
		//sh->arg[i] = ft_strtrimignore(sh->arg[i]);
		i >= 1 ? ft_printf(" ") : 0;
		ft_printf("\x1b[38;2;255;235;202m%s", sh->arg[i]);
		free(tmp);
		i++;
	}
	if (!flag_n)
		ft_printf("\n");		//ce \n ira dans la redirection de fichier,
								//1 autre pour remettre a la ligne dans le terminal
}
