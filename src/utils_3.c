#include "sh.h"

char *join_path(const char *path, const char *command)
{
	char	*new;

	new = ft_strnew(ft_strlen(path) + ft_strlen(command) + 1);
	new = ft_strcpy(new, path);
	new = ft_strcat(new, "/");
	new = ft_strcat(new, command);
}
