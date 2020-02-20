#include "../includes/minishell.h"

void found(t_shell *sh, char **paths)
{
	int		j;
	char 	*cmd;
	char *newargv[] = { NULL, "-la", NULL };
	char *newenviron[] = { NULL };

	j = 0;
	while (paths[j])
	{
		cmd = ft_strjoin(paths[j], "/");
		cmd = ft_strjoin(cmd, sh->cmd);
		ft_printf("commande %s\n", cmd);
		ft_printf("commande %d\n", execve(cmd, newargv, newenviron));
		j++;
	}
}

void handle_bin(t_shell *sh, char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			ft_printf("trouve %s\n", env[i] + 5);
			paths = ft_split(env[i] + 5, ':');
			found(sh, paths);
		}
		i++;
	}
}
