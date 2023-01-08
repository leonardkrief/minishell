/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 06:37:28 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/08 03:15:57 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(char *str)
{
	
}

int	exec_tree(t_btree *tree)
{
	t_list	*node;

	node = (t_list *) tree->node;
	if (ft_strncmp((char *) node->content, "||", 3))
	{
		if (exec_tree(tree->l) == 0)
			return (exec_tree(tree->r));
		else
			return (1);
	}
	else if (ft_strncmp((char *) node->content, "&&", 3))
	{
		if (exec_tree(tree->l) == 1)
			return (exec_tree(tree->r));
		else
			return (0);
	}
	else
		return (exec_command((char *) node->content));
}



// dans quel ordre se lance la commande (a && b) | c ?