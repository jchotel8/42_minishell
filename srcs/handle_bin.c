/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:36:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/23 19:48:29 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_find_cmd(t_shell *sh, char **paths)
{
	int			i;
	char		*cmd;
	struct stat	buf;
	pid_t		child;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, sh->cmd[0]);
		if (!stat(cmd, &buf))	//stat = trouver le fichier && signal = verifier les droits
			break ;
		i++;
	}
	if (!paths[i])
		ft_printf("\x1b[38;2;255;235;202mzsh: command not found: %s\n", sh->cmd[0]);
	else
	{
		if (!(child = fork()))
			execve(cmd, sh->cmd, ft_lst_to_array(sh->env));
		wait(&child);
	}
}

void	handle_bin(t_shell *sh)
{
	char	**possible_paths;
	t_list	*tmp;

	tmp = sh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "PATH=", 5))
		{
			possible_paths = ft_split(tmp->content + 5, ':');
			ft_find_cmd(sh, possible_paths);
		}
		tmp = tmp->next;
	}
}
