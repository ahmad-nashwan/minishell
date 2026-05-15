#include "../../inc/minishell.h"

t_code	pwd(int fd_out)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
		return (INTERNAL_ERROR);
	ft_putendl_fd(wd, fd_out);
	free(wd);
	return (OK);
}
