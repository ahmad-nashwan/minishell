/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/06/13 00:06:58 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	visual_len(char *s)
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

void	get_distro(char *out, size_t size)
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
	usleep(15000);
	print_empty_line();
	print_centered_line("                     __  ", BOLD VIOLET);
	print_centered_line("   ____  ____ ______/ /_ ", BOLD VIOLET);
	print_centered_line("  / __ \\/ __ `/ ___/ __ \\", BOLD VIOLET);
	print_centered_line(" / / / / /_/ (__  ) / / /", BOLD VIOLET);
	print_centered_line("/_/ /_/\\__,_/____/_/ /_/ ", BOLD VIOLET);
	usleep(25000);
	print_empty_line();
	print_centered_line("NotAnotherSHELL", STEEL_BLUE);
	print_empty_line();
	print_bottom_border(distro);
	usleep(40000);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
