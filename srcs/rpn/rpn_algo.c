/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 17:53:12 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rpn_isspecial(t_rpn *rpn, int i)
{
	int		len;
	t_list	*lst;

	rpn->current = NULL;
	lst = rpn->specials;
	while (lst)
	{
		len = ft_strlen(lst->content);
		if (ft_strncmp(rpn->s + i, lst->content, len) == 0)
			return (rpn->current = lst, 1);
		lst = lst->next;
	}
	return (0);
}

void	*rpn_handle_parenthesis(t_rpn *rpn)
{
	char	*parenthesis;
	t_list	*tmp;

	parenthesis = rpn->current->content;
	if (!ft_strncmp(parenthesis, "(", 2))
	{
		tmp = ft_lstnew_rpn(ft_strndup(")", -1), 0);
		if (!tmp)
			return (ft_puterror(FAILED_MALLOC, (char *)"rpn_handle_prthss"));
		ft_lstadd_front(&rpn->ops, tmp);
	}
	else if (!ft_strncmp(parenthesis, ")", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, ")", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (ft_puterror(ERROR_EXPRESSION, NULL));
		else
			rpn_pop_opsdel(rpn);
	}
	return (parenthesis);
}

void	*rpn_handle_operators(t_rpn *rpn)
{
	t_list	*op;
	t_list	*tmp;

	op = rpn->current;
	while (rpn->ops && (op->precedence <= rpn->ops->precedence))
		rpn_pop_ops(rpn);
	tmp = ft_lstnew_rpn(ft_strndup(op->content, -1), op->precedence);
	if (!tmp)
		return (NULL);
	ft_lstadd_front(&rpn->ops, tmp);
	return (tmp);
}

void	*rpn_isspecialtreatment(t_rpn *rpn)
{
	if (ft_match_list(rpn->current->content, rpn->parenthesis))
		return (rpn_handle_parenthesis(rpn));
	else
		return (rpn_handle_operators(rpn));
}

void	*rpn_generate_treatment(t_rpn *rpn, int *i, int j)
{
	t_list	*tmp;

	rpn->prev = rpn->current;
	while (rpn->s[*i] && ft_strchr(rpn->blanks, rpn->s[*i]))
		(*i)++;
	j = *i;
	while (rpn->s[*i] && !rpn_isspecial(rpn, *i))
		(*i)++;
	if (*i != j)
	{
		if (rpn->prev && !ft_strncmp(rpn->prev->content, ")", 2))
			return (rpn->current = ft_lstlast(rpn->out), NULL);
		else if (rpn->s[*i] == '(')
			return (rpn->current = ft_lstlast(rpn->out), NULL);
		tmp = ft_lstnew_rpn(ft_strtrim_lkrief(ft_strndup(rpn->s + j, *i - j),
					rpn->blanks), 0);
		if (!tmp)
			return (ft_puterror(FAILED_MALLOC, (char *)"rpn_generate_tr..."));
		ft_lstadd_back(&rpn->out, tmp);
	}
	if (rpn->s[*i])
	{
		// int check = rpn_isspecialtreatment(rpn);
		if (!rpn_isspecialtreatment(rpn))
			return (NULL);
		if (*i == j && rpn->prev && !ft_strncmp(rpn->prev->content, "(", 2)
			&& ft_match_list(rpn->current->content, rpn->specials))
			return (NULL);
		if (*i == j && rpn->prev && ft_match_list(rpn->prev->content,
				rpn->specials) && !ft_strncmp(rpn->current->content, ")", 2))
			return (NULL);
		*i += ft_strlen(rpn->current->content);
	}

	printf("_________(%d)_________\nout =\t", *i);
	ft_lstprint(rpn->out);
	printf("ops =\t");
	ft_lstprint(rpn->ops);
	printf("rpn.s + i = '%s'\n", rpn->s + *i);
	if (rpn->current)
		printf("rpn.current = '%s'\n", (char *) rpn->current->content);
	else
		printf("rpn.current = (null)\n");

	return (rpn);
}

t_rpn	*generate_rpn(t_rpn *rpn, char *str)
{
	int		i;

	i = 0;
	init_rpn(rpn, str);
	while (rpn->s[i])
	{
		if (!rpn_generate_treatment(rpn, &i, 0))
		{
			if (rpn->current)
				ft_puterror(ERROR_RPN_PARSING, rpn->current->content);
			else
				ft_puterror(ERROR_RPN_PARSING, "(");
			return (rpn);
		}
	}
	if (rpn_popending(rpn))
		return (rpn);
	
	rpn->current = NULL;
	printf("_________(%d)_________\nout =\t", i);
	ft_lstprint(rpn->out);
	printf("ops =\t");
	ft_lstprint(rpn->ops);
	printf("rpn.s + i = '%s'\n", rpn->s + i);
	if (rpn->current)
		printf("rpn.current = '%s'\n", (char *) rpn->current->content);
	else
		printf("rpn.current = (null)\n");
	
	return (rpn);
}