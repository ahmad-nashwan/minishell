/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anashwan <anashwan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:42:11 by anashwan          #+#    #+#             */
/*   Updated: 2025/09/09 17:57:45 by anashwan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	if (!lst || !(*lst) || !del)
		return ;
	while (*lst)
	{
		del((*lst)->content);
		next = (*lst)->next;
		free(*lst);
		(*lst) = next;
	}
	*lst = NULL;
}
