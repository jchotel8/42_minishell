/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:33 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 05:59:48 by jchotel          ###   ########.fr       */
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

void	next_shell_line(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line = 0;
}

void	next_shell_cmd(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line++;
}

void	debug_shell(t_shell *sh)
{
	printf("\x1b[38;2;70;70;70m..............\n");
	printf("READ\t: %s.\n", sh->read);
	ft_print_array(sh->lines, "LINES\t:", 1);
	printf("CMD\t: %s.\n", sh->cmd);
	ft_print_array(sh->arg, "ARG\t:", 1);
	printf("WD\t: %s.\n", sh->wd);
	printf("LINE\t: %d.\n\033[0;0m\x1b[38;2;255;235;202m", sh->i_line);
}
