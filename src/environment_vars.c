
#include "sh.h"

void					run_env(t_sh *sh)
{
	int					i;
	t_bool				valid;

	i = 1;
	valid = TRUE;
	if (sh->cmd[i] != NULL)
	{
		while (sh->cmd[i] && valid)
		{
			if (ft_strchr(sh->cmd[i], '=') == NULL)
				valid = FALSE;
			else
				set_env(sh->cmd[i], sh);
			i++;
		}
	}
	if (valid)
	{
		print_env(sh->env_var);
		unset_env(sh);
	}
	ft_putstr("env: ");
	ft_putstr(sh->cmd[i]);
	ft_putendl("No such file or directory");
}


void		print_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] != NULL)
		ft_putendl(env[i++]);
}

void		set_env(char *name, t_sh *sh)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	tmp = ft_strsub(name, 0, ft_indexof(name, '='));
	i = find(sh->env_var, tmp);
	free(tmp);
	if (i == -1)
	{
		sh->env_var[sh->env_size] = ft_strdup(name);
	}
	else
	{
		ft_strdel(&sh->env_var[i]);
		sh->env_var[i] = ft_strdup(name);
	}
}

void		unset_env(t_sh *sh)
{
	ft_arrdel(&sh->env_var);
	sh->env_var = ft_arrdup(sh->env_var_bckp);
}
