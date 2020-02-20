#include "../includes/minishell.h"

t_shell	*init_shell()
{
	t_shell *sh;

	if (!(sh = malloc(sizeof(struct s_shell))))
		return (NULL);
	sh->read = 0;
	sh->lines = 0;
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i = 0;
	//if (!getwd(sh->wd))
	//	printf("failed\n");
	return (sh);
}

void	next_shell(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i = 0;
}

void	reset_shell(t_shell *sh)
{
	sh->cmd = 0;
	sh->arg = 0;
	if (!(getcwd(sh->wd, sizeof(sh->wd))))
		printf("failed to init WD\n");
	sh->i++;
}

void	debug_shell(t_shell *sh)
{
	int i;

	i = 0;
	printf("\x1b[38;2;70;70;70m..............\n");
	printf("READ : %s.\n", sh->read);
	while (sh->lines && sh->lines[i])
	{
		printf("LINE : [%d] %s.\n", i, sh->lines[i]);
		i++;
	}
	printf("CMD  : %s.\n", sh->cmd);
	i = 0;
	while (sh->arg && sh->arg[i])
	{
		printf("ARG  : [%d] %s.\n", i, sh->arg[i]);
		i++;
	}
	printf("WD   : %s.\n", sh->wd);
	printf("I    : %d.\n", sh->i);
}

void	handle_cmd(t_shell *sh, char **env)
{
	//attention il faut aussi s'occuper des excecutables!!
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
	ft_printf("\x1b[38;2;255;235;202mzsh: command not found: %s\n\x1b[38;2;30;30;30m", sh->cmd);
}