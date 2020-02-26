/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:28:33 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 19:56:43 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_shell(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_pipe = 0;
	sh->i_line = 0;
}

t_shell	*init_shell(void)
{
	t_shell	*sh;

	if (!(sh = malloc(sizeof(struct s_shell))))
		return (NULL);
	sh->read = 0;
	sh->pipes = 0;
	sh->lines = 0;
	clean_shell(sh);
	return (sh);
}

void	next_shell_line(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_line++;
	sh->i_pipe = 0;
}

void	next_shell_pipe(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i_pipe++;
}

void	free_shell(t_shell *sh)
{
	free(sh->read);
	ft_freearray(sh->lines, ft_arraysize(sh->lines));
	ft_freearray(sh->cmd, ft_arraysize(sh->cmd));
	ft_lstclear(&sh->env, free);
	free(sh);
}

void	debug_shell(t_shell *sh)
{
	printf("\x1b[38;2;70;70;70m..............\n");
	printf("READ\t: %s.\n", sh->read);
	ft_print_array(sh->lines, "LINES\t:", 1);
	ft_print_array(sh->pipes, "TASKS\t:", 1);
	if (sh->cmd)
		printf("CMD\t: %s.\n", sh->cmd[0]);
	ft_print_array(sh->arg, "ARG\t:", 1);
	printf("WD\t: %s.\n", sh->wd);
	printf("LINE\t: %d.\n", sh->i_line);
	printf("TASK\t: %d.\n", sh->i_pipe);
	printf("\033[0;0m\x1b[38;2;255;235;202m");
}
