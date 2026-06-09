#include "minishell.h"
#include <sys/utsname.h>

#define TOTAL_WIDTH		60
#define INNER_WIDTH		(TOTAL_WIDTH - 2)
#define COLOR			"\033[38;5;111m"

#define ME "anashwan"
#define PARTNER "masad"

static void	print_dashes(int n)
{
	while (n-- > 0)
		ft_putstr_fd("─", STDOUT_FILENO);
}

static void	print_top_border( char *username)
{
	int	dashes;

	dashes = TOTAL_WIDTH - 7 - (int)ft_strlen(username);
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

static void	print_bottom_border( char *distro)
{
	int	dashes;

	dashes = TOTAL_WIDTH - 7 - (int)ft_strlen(distro);
	if (dashes < 0)
		dashes = 0;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("└", STDOUT_FILENO);
	print_dashes(dashes);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(BOLD, STDOUT_FILENO);
	ft_putstr_fd(distro, STDOUT_FILENO);
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

static void	print_centered_line( char *text,  char *text_color)
{
	int	tlen;
	int	padding;
	int	i;

	tlen = ft_strlen(text);
	padding = (INNER_WIDTH - tlen) / 2;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	i = 0;
	while (i++ < padding)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(text_color, STDOUT_FILENO);
	ft_putstr_fd(text, STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	i = padding + tlen;
	while (i++ < INNER_WIDTH)
		ft_putchar_fd(' ', STDOUT_FILENO);
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("│", STDOUT_FILENO);
	ft_putstr_fd(RESET, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

static void	get_distro(char *out, size_t size)
{
	FILE	*f;
	char	line[256];
	char	*p;

	ft_strlcpy(out, "Linux", size);
	f = fopen("/etc/os-release", "r");
	if (!f)
		return ;
	while (fgets(line, sizeof(line), f))
	{
		if (ft_strncmp(line, "NAME=", 5) == 0)
		{
			p = line + 5;
			if (*p == '"')
				p++;
			ft_strlcpy(out, p, size);
			p = out;
			while (*p && *p != '"' && *p != '\n')
				p++;
			*p = '\0';
			break ;
		}
	}
	fclose(f);
}

void	print_banner(t_shell *shell)
{
	char	distro[64];
	char	byline[64];
	char	*username;

	username = get_env_value(shell->env_list, "USER");
	if (!username)
		username = "user";
	get_distro(distro, sizeof(distro));
	ft_strlcpy(byline, "by ", sizeof(byline));
	ft_strlcat(byline, ME, sizeof(byline));
	ft_strlcat(byline, " & ", sizeof(byline));
	ft_strlcat(byline, PARTNER, sizeof(byline));
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	print_top_border(username);
	usleep(20000);
	print_empty_line();
	print_centered_line("nash", BOLD COLOR);
	usleep(40000);
	print_centered_line(byline, DIM);
	usleep(30000);
	print_centered_line("42 Amman", DIM);
	usleep(30000);
	print_empty_line();
	usleep(30000);
	print_bottom_border(distro);
	usleep(80000);
}