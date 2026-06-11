#include "minishell.h"
#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>

#define TOTAL_WIDTH		60
#define INNER_WIDTH		(TOTAL_WIDTH - 2)
#define COLOR			"\033[38;5;111m"

static int	visual_len( char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if ((*s & 0x80) == 0)
			s++;
		else if ((*s & 0xE0) == 0xC0)
			s += 2;
		else if ((*s & 0xF0) == 0xE0)
			s += 3;
		else
			s += 4;
		len++;
	}
	return (len);
}

static void	print_dashes(int n)
{
	while (n-- > 0)
		ft_putstr_fd("─", STDOUT_FILENO);
}

static void	print_top_border( char *username)
{
	int	dashes;

	dashes = TOTAL_WIDTH - 7 - visual_len(username);
	if (dashes < 0)
		dashes = 0;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("┌───[", STDOUT_FILENO);
	ft_putstr_fd(BOLD VIOLET, STDOUT_FILENO);
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

	dashes = TOTAL_WIDTH - 7 - visual_len(distro);
	if (dashes < 0)
		dashes = 0;
	ft_putstr_fd(COLOR, STDOUT_FILENO);
	ft_putstr_fd("└", STDOUT_FILENO);
	print_dashes(dashes);
	ft_putstr_fd("[", STDOUT_FILENO);
	ft_putstr_fd(BOLD VIOLET, STDOUT_FILENO);
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

	tlen = visual_len(text);
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
	char	*username;

	username = get_env_value(shell->env_list, "USER");
	if (!username)
		username = "user";
	get_distro(distro, sizeof(distro));
	write(STDOUT_FILENO, "\033[2J\033[H", 7);
	print_top_border(username);
	usleep(30000);
	print_empty_line();
	print_centered_line("nash", BOLD VIOLET);
	usleep(40000);
	print_centered_line("42 amman", STEEL_BLUE);
	usleep(40000);
	print_centered_line("· 2026 ·", STEEL_BLUE);
	usleep(40000);
	print_empty_line();
	usleep(40000);
	print_bottom_border(distro);
	usleep(90000);
	ft_putstr_fd("\n", STDOUT_FILENO);
}