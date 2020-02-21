/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:17 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 02:30:36 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_shell *sh)
{
	(void)sh;
	if (!sh->arg)
	{
		if (!(getcwd(sh->wd, sizeof(sh->wd))))
			printf("failed to init WD\n");
		ft_printf("\x1b[38;2;255;235;202m%s\n", sh->wd);
	}
	else
		ft_printf("\x1b[38;2;255;235;202mpwd: too many arguments\n");
}
