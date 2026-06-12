/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 21:40:54 by anashwan          #+#    #+#             */
/*   Updated: 2026/05/26 21:40:55 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_dashes(int n)
{
	while (n-- > 0)
		ft_putstr_fd("─", STDOUT_FILENO);
}

void	print_top_border(char *username)
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

void	print_bottom_border(char *distro)
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

void	print_empty_line(void)
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

void	print_centered_line(char *text, char *text_color)
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
