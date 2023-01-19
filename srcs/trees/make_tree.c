/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 11:25:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_getenv(char **envp, t_data *data)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			data->path = ft_split(envp[i] + 5, ':');
			if (!data->path)
				return (ft_puterror(FAILED_MALLOC, (char *)"ft_getenv"));
		}
	}
	return (data->path);
}

t_list	*ft_isoperator_treatment(t_data *data, t_list *out, t_list *list)
{
	t_btree	*tree;

	tree = new_tree(out->content, data);
	if (!list)
		return (ft_puterror(ERROR_EXPRESSION, NULL), free_tree(tree), NULL);
	tree->r = (t_btree *) list->content;
	// probleme sur ce free ?
	// il faut free le contenu de list qui peut etre un arbre nn ?
	free(ft_lstpop(&list));
	if (!list)
		return (ft_puterror(ERROR_EXPRESSION, NULL), free_tree(tree), NULL);
	tree->l = (t_btree *) list->content;
	// probleme sur ce free ?
	// il faut free le contenu de list qui peut etre un arbre nn ?
	free(ft_lstpop(&list));
	ft_lstadd_front(&list, ft_lstnew(tree));
	return (list);
}

t_list	*get_tree_treatment(char *str, t_rpn rpn_var, t_data *data)
{
	t_list	*out;
	t_list	*list;

// si echec,
// ft_getenv doit retourner NULL en freeant toutes ses variables locales
// rpn aussi
	if (!str)
		return (NULL);
	if (rpn_var.current)
		return (ft_puterror(ERROR_RPN, (char *)rpn_var.current->content));
	list = NULL;
	out = rpn_var.out;
	while (out)
	{
		if (ft_match_list(out->content, rpn_var.operators))
		{
			if (!ft_isoperator_treatment(data, out, list))
				return (list);
		}
		else
			ft_lstadd_front(&list, ft_lstnew(new_tree(out->content, data)));
			// tree = (t_btree*)list->content;
		out = out->next;
	}
	return (list);
}

t_btree	*get_tree(char *str, char **env, t_data *data)
{
	t_rpn	rpn_var;
	t_btree	*tree;
	t_list	*list;

	if (!ft_getenv(env, data))
		return (NULL);
	if (!rpn(&rpn_var, str))
		return (NULL);
	list = get_tree_treatment(str, rpn_var, data);
	if (!list)
		return (free_rpn(&rpn_var), NULL);
	tree = list->content;
	// il faut free la liste, bien verifier qu'on free tout car il ya
	// des arbres en content ?
	return (tree);
}
