#ifndef SH_H
#	define SH_H

#	include <sys/types.h>
#	include <sys/wait.h>
#	include <signal.h>
#	include "libft.h"
#include <stdio.h>

typedef struct	s_sh
{
	char		**cmd;
	char		**env_var;
	char		**env_var_bckp;
	char		**com_locations;
	int			env_size;
	pid_t		child;
}				t_sh;

void			change_dir(t_sh *sh);

void			exit_sh(t_sh *sh);

void			run_env(t_sh *sh);

void			print_env(char **env);

void			set_env(char *name, t_sh *sh);

void			unset_env(t_sh *sh);

void			echo_word(t_sh *sh);

char			**getcmd();

void			init_sh(t_sh *sh, char **env);

int				find(char **env, char *var);

char			*join_path(const char *path, const char *command);

int				cnt_words(char const *s, char c);

#endif
