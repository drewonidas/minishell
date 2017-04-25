#include "sh.h"

char			**getcmd()
{
	char		*line;
	int			size;
	char		**tmp;
	char		**cmd;
	int			 i;

	i = 0;
	tmp = NULL;
	line = ft_strnew(5000);
	size = read(0, line, 5000);
	line[size] = '\0';
	tmp = ft_strsplit((char const *)line, ' ');
	int d = cnt_words(line, ' ');
	cmd = (char **) malloc((size_t) sizeof(char *) * (d + 2));
	while (tmp[i] != NULL)
	{
		cmd[i] = ft_strtrim((char const *)tmp[i]);
		i++;
	}
	cmd[i] = NULL;
	ft_strdel(&line);
	ft_arrdel(&tmp);
	return (cmd);
}

int				find(char **env, char *var)
{
	int			i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(var, env[i], ft_strlen(var) - 1)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
/*
TODO: implement env_var as linked list
 */
void			init_sh(t_sh *sh, char **env)
{
	int			i;
	char		*tmp;
	const char	*path = "PATH";

	i = 0;
	while (env[i++])
		;
	sh->env_size = i;
	sh->env_var = ft_arrdup(env);
	sh->env_var_bckp = ft_arrdup(env);
	i = find(sh->env_var, (char *)path);
	if (i != -1)
	{
		tmp = ft_strsub(env[i], ft_indexof(env[i], '=') + 1, ft_strlen(env[i]) - 6);
		sh->com_locations = ft_strsplit(tmp, ':');
		free(tmp);
	}
	sh->cmd = NULL;
	sh->child = 0;
}

void			exit_sh(t_sh *sh)
{
	pid_t		tmp;

	tmp = sh->child;
	if (sh->cmd != NULL)
		ft_arrdel(&sh->cmd);
	if (sh->env_var != NULL)
		ft_arrdel(&sh->env_var);
	if (sh->com_locations != NULL)
		ft_arrdel(&sh->com_locations);
	if (sh->env_var_bckp != NULL)
		ft_arrdel(&sh->env_var_bckp);
	free(sh);
	sh = NULL;
	if (tmp)
		kill(tmp, SIGTERM);
//	exit(0);
}
