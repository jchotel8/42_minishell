/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:17 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 03:41:16 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pwd(t_shell *sh)
{
	if (!sh->arg)
	{
		if (!(getcwd(sh->wd, sizeof(sh->wd))))
			printf("failed to init WD\n");
		ft_printf("\x1b[38;2;255;235;202m%s\n", sh->wd);
	}
	else
		ft_printf("\x1b[38;2;255;235;202mpwd: too many arguments\n");
}

char	*get_wd(t_shell *sh)
{
	char	**files;
	int		i;

	i = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	files = ft_split(sh->wd, '/');
	while (files && files[i])
		i++;
	return (files[i - 1]);
}
