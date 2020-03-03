/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:35 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/03 12:27:12 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cd(t_shell *sh)
{
	if (sh->arg[1])
		ft_printf("\x1b[38;2;255;235;202mcd: too many arguments\n");
	else if (chdir(sh->arg[0]) == -1)
		ft_printf("\x1b[38;2;255;235;202mcd: no such file or "
			"directory : %s\n", sh->arg[0]);
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("\x1b[38;2;255;235;202mfailed to get WD\n");
}
