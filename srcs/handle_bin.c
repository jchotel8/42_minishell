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

char **ft_array_add_front(char **array, void *data)
{
	t_list *list;
	list = ft_array_to_lst(array);
	ft_lstadd_front(&list, ft_lstnew(data));
	/* penser a tout free*/
	return (ft_lst_to_array(list));
}

void	ft_exec_cmd(t_shell *sh, char *cmd)
{
	if (!fork())
	{
		ft_printf("\x1b[38;2;255;235;202m");
		execve(cmd, sh->arg, ft_lst_to_array(sh->env));
	}
	/*if(sh->i_task)
		close(sh->pipefd); je sais pas si c'est utile*/
}

void	ft_find_cmd(t_shell *sh, char **paths)
{
	int			i;
	char		*cmd;
	struct stat	buf;

	i = 0;
	sh->arg = ft_array_add_front(sh->arg, sh->cmd);
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
	wait(NULL);
	ft_exec_cmd(sh, cmd);
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
