/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/04 19:18:45 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*new_node(void *node)
{
	t_btree	*t;

	t = malloc(sizeof(*t));
	if (!t)
		return (NULL);
	t->node = node;
	t->r = NULL;
	t->l = NULL;
	return (t);
}

void	add_left(t_btree **tree, t_btree *left_son)
{
	t_btree	*t;

	t = *tree;
	if (t == NULL)
		*tree = left_son;
	t->l = left_son;
}

void	add_right(t_btree **tree, t_btree *right_son)
{
	t_btree	*t;

	t = *tree;
	if (t == NULL)
		*tree = right_son;
	t->l = right_son;
}

void	free_tree(t_btree *t)
{
	if (t->r)
		free_tree(t->r);
	if (t->l)
		free_tree(t->l);
	free(t->node);
	free(t);
}
