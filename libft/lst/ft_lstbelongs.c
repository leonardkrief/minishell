/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbelongs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 02:00:04 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/05 06:00:36 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstbelongs(t_list *lst, void *does_it, int (*cmp)(void *, void *), int (*len)(void *))
{
	while (lst)
	{
		if (cmp(does_it, lst->content) == 0)
			return (len(lst->content));
		lst = lst->next;
	}
	return (0);
}
