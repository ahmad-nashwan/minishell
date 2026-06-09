#include "minishell.h"

#define PATH_MAX 4096

static void	shorten_path(char *cwd, char *out)
{
	char	*home;
	int		i;

	home = getenv("HOME");
    i = 0;
    (void)i;
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		out[0] = '~';
		i = 1;
		ft_strlcpy(out + 1, cwd + ft_strlen(home), PATH_MAX - 1);
	}
	else
		ft_strlcpy(out, cwd, PATH_MAX);
}

void	print_prompt_line(t_shell *shell)
{
	char	cwd[PATH_MAX];
	char	path[PATH_MAX];
	char	*username;

	username = get_env_value(shell->env_list, "USER");
	if (!username)
		username = "user";
	if (!getcwd(cwd, sizeof(cwd)))
		ft_strlcpy(cwd, "?", sizeof(cwd));
	shorten_path(cwd, path);
	ft_putstr_fd(C_6, STDOUT_FILENO);
	ft_putstr_fd(username, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putstr_fd(DIM, STDOUT_FILENO);
	ft_putstr_fd(" · ", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putstr_fd(C_4, STDOUT_FILENO);
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}