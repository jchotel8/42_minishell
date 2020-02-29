/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:33 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 06:48:23 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	start_shell_line(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_task = 0;
	sh->i_line = 0;
}

t_shell	*init_shell(void)
{
	t_shell	*sh;

	if (!(sh = malloc(sizeof(struct s_shell))))
		return (NULL);
	sh->read = 0;
	sh->tasks = 0;
	sh->lines = 0;
	start_shell_line(sh);
	return (sh);
}

void	next_shell_line(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line++;
	sh->i_task = 0;
}

void	next_shell_task(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_task++;
}

void	debug_shell(t_shell *sh)
{
	printf("..............\n");
	printf("READ\t: %s.\n", sh->read);
	ft_print_array(sh->lines, "LINES\t:", 1);
	ft_print_array(sh->tasks, "TASKS\t:", 1);
	printf("CMD\t: %s.\n", sh->cmd[0]);
	ft_print_array(sh->arg, "ARG\t:", 1);
	printf("WD\t: %s.\n", sh->wd);
	printf("LINE\t: %d.\n", sh->i_line);
	printf("TASK\t: %d.\n", sh->i_task);
}
