/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_bin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 20:36:01 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 06:50:51 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_find_cmd(t_shell *sh, char **paths)
{
	int			i;
	char		*cmd;
	char		*argv[] = {sh->cmd, "-la", NULL};	//à remplacer par sh->arg, avec sh->arg[0] = cmd et sh->arg[last] = NULL
	struct stat	buf;
	pid_t		child;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], "/");
		cmd = ft_strjoin(cmd, sh->cmd);
		if (!stat(cmd, &buf))	//stat = trouver le fichier && signal = verifier les droits
			break ;
		i++;
	}
	if (!paths[i])
		ft_printf("\x1b[38;2;255;235;202mzsh: command not found: %s\n", sh->cmd);
	else
	{
		if (!(child = fork()))
		{
			ft_printf("\x1b[38;2;255;235;202mexec : %d\n", execve(cmd, argv, ft_lst_to_array(sh->env)));
		//	//exit(1); pas sure de l'utilité de ca
		}
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
