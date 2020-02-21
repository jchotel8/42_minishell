/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:12:08 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 05:42:21 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_cmd(t_shell *sh, char **env)
{
	if (!ft_strcmp(sh->cmd, "echo"))
		return (handle_echo(sh));
	if (!ft_strcmp(sh->cmd, "cd"))
		return (handle_cd(sh));
	if (!ft_strcmp(sh->cmd, "pwd"))
		return (handle_pwd(sh));
	if (!ft_strcmp(sh->cmd, "exit"))
		return (exit(0));
	if (!ft_strcmp(sh->cmd, "unset"))
		return ;
	if (!ft_strcmp(sh->cmd, "env"))
		return (handle_env(sh, env));
	if (!ft_strcmp(sh->cmd, "export"))
		return ;
	else
		return (handle_bin(sh, env));
}

int		main()//int ac, char **av, char **env)
{
	t_shell	*sh;

	if (ac > 0)
	{
		av[1] = 0;
		sh = init_shell();
		ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		sh->env = env;
		while (get_next_line(0, &sh->read) > 0)
		{
			next_shell(sh);
			parsing_read(sh);
			while (sh->lines[sh->i_line])
			{
				parsing_line(sh);
				//debug_shell(sh);
				handle_cmd(sh, env);
				sh->i_line++;
			}
			ft_printf(PROMPT, "MINISHELL", get_wd(sh));
		}
		printf("last read : \"%s\"\n", sh->read);
		free(sh->read);
	}

}
