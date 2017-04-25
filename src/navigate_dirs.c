#include "sh.h"

int 		change(t_sh *sh, char *new_dir)
{
	int 	j;
	int		result;
	char	*cwd;
	char	*tmp;

	result = 0;
	j = find(sh->env_var, "PWD");
	cwd = ft_strnew(ft_strlen(sh->env_var[j]));
	cwd = getcwd(cwd, ft_strlen(sh->env_var[j]));
	tmp = join_path(cwd, new_dir);
	result = chdir((const char *)tmp);
	ft_strdel(&cwd);
	ft_strdel(&tmp);
	return (result);
}

void		get_home(t_sh *sh, char **dir)
{
	int		i;
	char	*tmp;
	char	*new_dir;

	i = find(sh->env_var, "HOME");
	new_dir = *dir;
	if (ft_strlen(new_dir) > 1)
		tmp = join_path(ft_strchr(sh->env_var[i], '/'), &new_dir[1]);
	else
		tmp = ft_strdup(ft_strchr(sh->env_var[i], '/'));
	ft_strdel(dir);
	*dir = tmp;
}

// TODO: change cd ~ to work with any directory e.g cd ~/Documents
void		change_dir(t_sh *sh)
{
	int		result;
	int		cnt;
	char	*new_dir;

	cnt = 0;
	new_dir = NULL;
	result = 0;
	while (sh->cmd[cnt])
		cnt++;
	if (cnt < 2)
		new_dir = ft_strdup("~");
	else
		new_dir = ft_strdup((const char *)sh->cmd[1]);
	if (new_dir[0] == '~')
		get_home(sh, &new_dir);
	if (new_dir[0] == '/')
		result = chdir((const char *)new_dir);
	else
		result = change(sh, new_dir);
	if (result == -1)
		printf("mDash: %s: no such file or directory\n", new_dir);
	ft_strdel(&new_dir);
}
