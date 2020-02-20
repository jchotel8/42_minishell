#include "../includes/minishell.h"

void prep_arg(t_shell *sh)
{
	char *next;

	while (ft_strcount(sh->read, '"') % 2)
	{
		ft_printf("dquote>");
		get_next_line(0, &next);
		sh->read = ft_strjoin(sh->read, "\n");
		sh->read = ft_strjoin(sh->read, next);
		free(next);
	}
	sh->lines = ft_split(sh->read, '"');
}

void parsing_read(t_shell *sh)
{
	prep_arg(sh);
	//sh->lines = ft_split(sh->read, ';');
	//free(sh->read);
}

void parsing_line(t_shell *sh)
{
	int i;
	int len;

	i = 0;
	len = 0;
	sh->arg = ft_split(sh->lines[sh->i], ' ');
	sh->cmd = sh->arg[0];
	sh->arg = (sh->arg[1] ? &sh->arg[1] : NULL);
}
