/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 01:40:39 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/05 07:23:42 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpop(t_list **lst, t_list *to)
{
	t_list	*pop;

	pop = NULL;
	if (*lst)
	{
		pop = *lst;
		*lst = pop->next;
		pop->next = to;
	}
	return (pop);
}
