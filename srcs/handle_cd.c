#include "../includes/minishell.h"

void get_arg()
{

}

void handle_cd(t_shell *sh)
{
	if (sh->arg[1])
		ft_printf("\x1b[38;2;255;235;202mcd: too many arguments\n");
	else if (chdir(sh->arg[0]) == -1)
		ft_printf("\x1b[38;2;255;235;202mcd: no such file or directory : %s\n", sh->arg[0]);
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("\x1b[38;2;255;235;202mfailed to get WD\n");
}