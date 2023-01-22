/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:57:38 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/21 22:45:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "liblkriefft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*begin;
	t_list	*before;

	if (lst && *lst && del)
	{
		begin = *lst;
		while (begin)
		{
			before = begin;
			begin = begin->next;
			ft_lstdelone(before, *del);
		}
		*lst = NULL;
	}
}
