/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:33 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 02:28:38 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*init_shell(void)
{
	t_shell	*sh;

	if (!(sh = malloc(sizeof(struct s_shell))))
		return (NULL);
	sh->read = 0;
	sh->lines = 0;
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line = 0;
	return (sh);
}

void	next_shell(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line = 0;
}

void	reset_shell(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line++;
}

void	debug_shell(t_shell *sh)
{
	int i;

	i = 0;
	printf("\x1b[38;2;70;70;70m..............\n");
	printf("READ : %s.\n", sh->read);
	while (sh->lines && sh->lines[i])
	{
		printf("LINE : [%d] %s.\n", i, sh->lines[i]);
		i++;
	}
	printf("CMD  : %s.\n", sh->cmd);
	i = 0;
	while (sh->arg && sh->arg[i])
	{
		printf("ARG  : [%d] %s.\n", i, sh->arg[i]);
		i++;
	}
	printf("WD   : %s.\n", sh->wd);
	printf("I    : %d.\n", sh->i_line);
}
