/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:35 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 02:17:06 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cd(t_shell *sh)
{
	if (sh->arg[1])
		ft_printf("cd: too many arguments\n");
	else if (chdir(sh->arg[0]) == -1)
		ft_printf("cd: no such file or "
			"directory : %s\n", sh->arg[0]);
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to get WD\n");
}
