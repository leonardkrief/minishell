/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:37:28 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/07 06:47:18 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_btree *tree)
{
	t_list	*node;

	node = (t_list *) tree->node;
	if (ft_strncmp((char *) node->content, "|", 2))
}