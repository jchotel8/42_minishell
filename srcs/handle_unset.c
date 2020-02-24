/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <jchotel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 06:53:55 by jchotel           #+#    #+#             */
/*   Updated: 2020/02/21 08:08:22 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_unset(t_shell *sh)
{
	ft_list_remove_if(&sh->env, sh->arg[0], *ft_strncmp_auto); //peut être faire un join avec un = sur sh->arg[0] et option majuscule/minuscule ?
} //qu'est ce qui se passe si jai plusieurs arg?

void	handle_export(t_shell *sh)
{
	ft_lstadd_back(&sh->env, ft_lstnew(sh->arg[0])); //questce qui se passe si sh->arg n'est pas au format MAVARIABLE="blabla"?
}//est-ce quil faut mettre les " ?
