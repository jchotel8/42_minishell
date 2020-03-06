/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 02:31:27 by jchotel           #+#    #+#             */
/*   Updated: 2020/03/05 19:56:41 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	prep_read(t_shell *sh)
{
	char	*next;
	char	*tmp;

	while (ft_countquoteignore(sh->read) % 2)
	{
		ft_printf(">");
		get_next_line(0, &next);
		tmp = sh->read;
		sh->read = ft_strjoin(sh->read, "\n");
		free(tmp);
		tmp = sh->read;
		sh->read = ft_strjoin(sh->read, next);
		free(tmp);
		free(next);
	}
}

void	parsing_read(t_shell *sh)
{
	prep_read(sh);
	sh->lines = ft_splitignore(sh->read, ';', 1);
	free(sh->read);
	sh->read = 0;
}

void	parsing_line(t_shell *sh)
{
	sh->pipes = ft_splitignore(sh->lines[sh->i_line], '|', 1);
}

void	parsing_pipe(t_shell *sh)
{
	int		i;
	char	**cmd_arg;
	t_list	*lst;

	i = 0;
	lst = NULL;
	sh->redir = ft_splitignore(sh->pipes[sh->i_pipe], '>', 0);
	while (sh->redir[i]) //si > attention il faut aussi verifier dans le cas ou > est placé au début donc !sh->redir[1]
	{
        //sh->redir[i] = ft_replaceenvignore(sh, sh->redir[i]); 
		if (ft_strcmp(">", sh->redir[i]) == 0)
	 	{//cas ou sh->redir = ">"
	 		sh->type = 1;
	 		sh->redir[i] = "";
	 	}
	 	else
	 	{
			cmd_arg = ft_splitignore(sh->redir[i], ' ', 1);
			if (ft_strcmp(">", cmd_arg[0]) == 0)
			{//type > out
				sh->redir[i] = cmd_arg[1];
				cmd_arg++;
				cmd_arg++;	//skip > & cmd pour les args
			}
			else if (cmd_arg[0][0] == '>')
			{//type >out
				sh->redir[i] = cmd_arg[0];
				sh->redir[i] = ft_strtrim(sh->redir[i], ">");
				cmd_arg++; //skip >cmd pour les args
			}
			else
				sh->redir[i] = "";
			lst = ft_add_array_to_list(lst, cmd_arg);
		}
		i++;
	}
	sh->cmd = ft_lst_to_array(lst);
	sh->arg = (sh->cmd[1] ? &sh->cmd[1] : NULL);
	i = 0;
	while (sh->arg && sh->arg[i])
	{
	 	sh->arg[i] = ft_strtrimignore(sh->arg[i]); //wesh pourquoi on utilise se ft_strtrim trop moche!?
	 	i++;
	}
	i = 0;
}
