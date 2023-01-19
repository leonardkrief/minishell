/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 10:41:08 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*new_tree(void *node, t_data *data)
{
	t_btree	*t;

	t = ft_calloc(sizeof(*t), 1);
	if (!t)
		return (NULL);
	t->node = ft_strndup((char *)node, -1);
	if (!t->node)
		return (free(t), ft_puterror(FAILED_MALLOC, (char *)"new_tree"), NULL);
	t->data = data;
	t->l = NULL;
	t->r = NULL;
	return (t);
}

void	add_left(t_btree **tree, t_btree *left_son)
{
	t_btree	*t;

	t = *tree;
	if (t == NULL)
		*tree = left_son;
	else
		t->l = left_son;
}

void	add_right(t_btree **tree, t_btree *right_son)
{
	t_btree	*t;

	t = *tree;
	if (t == NULL)
		*tree = right_son;
	else
		t->l = right_son;
}

void	*free_tree(t_btree *t)
{
	if (t->r)
		free_tree(t->r);
	if (t->l)
		free_tree(t->l);
	if (t->node)
		free(t->node);
	if (t)
		free(t);
	return (NULL);
}
