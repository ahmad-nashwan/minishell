#include "minishell.h"
#include <sys/utsname.h>
#include <unistd.h>

/*
** All width ants are in VISUAL characters (terminal columns), not bytes.
** Box-drawing chars (─ │ ┌ etc.) are 3 bytes each but 1 visual column.
**
** TOTAL_WIDTH = 70 visual columns including the two border chars (┌ and ┐)
** INNER_WIDTH = 68 visual columns (the space between the borders)
**
** Top border layout:    ┌ ─ ─ ─ [ username ] ─ ─ ... ─ ┐
**   fixed parts = 7     (┌ + ─── + [ + ] + ┐)
**   dashes = TOTAL_WIDTH - 7 - ulen
**
** Bottom border layout: └ ─ ─ ... ─ [ sysname ] ─ ─ ─ ┘
**   fixed parts = 7     (└ + [ + ] + ─── + ┘)
**   dashes = TOTAL_WIDTH - 7 - slen
*/

#define TOTAL_WIDTH		70
#define INNER_WIDTH		68
#define COLOR			"\033[38;5;111m"
#define RESET			"\033[0m"
#define BOLD			"\033[1m"

static  char	*g_logo[] = {
	"   ____  ____ _ _____ / /_  ",
	"  / __ \\/ __ `// ___// __ \\ ",
	" / / / / /_/ /(__  )/ / / / ",
	"/_/ /_/\\__,_//____//_/ /_/  ",
	NULL
};

static void	print_dashes(int n)
{
	while (n-- > 0)
		ft_putstr_fd("─", STDOUT_FILENO);
}

static void	print_top_border( char *username)
{
	int	ulen;
	int	dashes;

	ulen = ft_strlen(username);
	dashes = TOTAL_WIDTH - 7 - ulen;
	if (dashes < 0)
		dashes = 0;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("┌───[", STDOUT_FILENO);
	ft_putstr_fd(BOLD, STDOUT_FILENO);
	ft_putstr_fd(username, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("]", STDOUT_FILENO);
	print_dashes(dashes);
	ft_putstr_fd("┐", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_bottom_border( char *sysname)
{
	int	slen;
	int	dashes;

	slen = ft_strlen(sysname);
	dashes = TOTAL_WIDTH - 7 - slen;
	if (dashes < 0)
		dashes = 0;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("└", STDOUT_FILENO);
	print_dashes(dashes);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(BOLD, STDOUT_FILENO);
	ft_putstr_fd(sysname, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("]───┘", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_empty_line(void)
{
	int	i;

	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	i = 0;
	while (i++ < INNER_WIDTH)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	print_logo_line( char *line)
{
	int	llen;
	int	padding;
	int	i;

	llen = ft_strlen(line);
	padding = (INNER_WIDTH - llen) / 2;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	i = 0;
	while (i++ < padding)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(BOLD, STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd(line, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	i = padding + llen;
	while (i++ < INNER_WIDTH)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

void	print_banner(t_shell *shell)
{
	struct utsname	uts;
	char			*username;
	char			*sysname;
	int				i;

	username = get_env_value(shell->env_list, "USER");
	if (!username)
		username = "user";
	if (uname(&uts) == 0)
		sysname = uts.sysname;
	else
		sysname = "unknown";
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	print_top_border(username);
	usleep(6000);
	print_empty_line();
	i = 0;
	while (g_logo[i])
	{
		print_logo_line(g_logo[i++]);
		usleep(30000);
	}
	print_empty_line();
	usleep(50000);
	print_bottom_border(sysname);
	usleep(100000);
}