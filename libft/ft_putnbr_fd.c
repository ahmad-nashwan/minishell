/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:38:49 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/10 19:58:14 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	num;
	long	e;

	e = n;
	if (e == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (e < 0)
	{
		write(fd, "-", 1);
		e *= -1;
	}
	if (e / 10 != 0)
		ft_putnbr_fd(e / 10, fd);
	num = (e % 10) + '0';
	write(fd, &num, 1);
}
