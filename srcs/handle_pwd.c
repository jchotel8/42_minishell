#include "../includes/minishell.h"

void handle_pwd(t_shell *sh)
{
	(void)sh;
	if (!sh->arg)
	{
		getwd(sh->wd);
		ft_printf("\x1b[38;2;255;235;202m%s\n", sh->wd);
	}
	else
		ft_printf("\x1b[38;2;255;235;202mpwd: too many arguments\n");
}
