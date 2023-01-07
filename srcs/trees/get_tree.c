/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 05:42:09 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_btree	*get_tree(char *str)
{
	t_rpn	rpn_var;
	t_list	*out;
	t_list	*list;
	t_btree	*tree;

	if (!str)
		return (NULL);
	rpn(&rpn_var, str);
	if (rpn_var.current)
	{
		printf ("Error or special case: %s\n", (char *) rpn_var.current->content);
		free_rpn(&rpn_var);
		return (NULL);
	}
	list = NULL;
	out = rpn_var.out;
	tree = NULL;
	while (out)
	{
		if (!ft_match_list(out->content, rpn_var.operators))
			ft_lstadd_front(&list, ft_lstnew(new_tree(out->content)));
		else
		{
			tree = new_tree(out->content);
			tree->r = (t_btree *) list->content;
			free(ft_lstpop(&list));
			tree->l = (t_btree *) list->content;
			free(ft_lstpop(&list));
			ft_lstadd_front(&list, ft_lstnew(tree));
		}
		out = out->next;
	}
	free_rpn(&rpn_var);
	return ((t_btree *) list->content);
}
