/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/05 19:21:47 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list *ft_lstnew_rpn(void *content, int precedence)
{
	t_list	*new;
	// if (content = NULL)
		//return (error_handler(t_rpn *rpn, NULL_FAILURE));
	new = ft_lstnew(content);
	new->precedence = precedence;
	return (new);
}

void	ft_lstappendcopy(t_list **lst, t_list *copy)
{
	t_list	*new;

	while (copy)
	{
		new = ft_lstnew_rpn(ft_strdup(copy->content, -1), copy->precedence);
		ft_lstadd_back(lst, new);
		copy = copy->next;
	}
}

void	init_rpn(t_rpn *rpn, char *to_parse)
{
	ft_memset(rpn, 0, sizeof(*rpn));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strdup(")", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strdup("(", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strdup("{", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strdup("}", -1), 0));
	ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strdup("|", -1), 1));
	ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strdup("&&", -1), 1));
	ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strdup("||", -1), 1));
	ft_lstappendcopy(&rpn->specials, rpn->operators);
	ft_lstappendcopy(&rpn->specials, rpn->parenthesis);
	rpn->blanks = ft_strdup("\t ", 2);
	rpn->s = to_parse;
}

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
		{
			rpn->current = lst;
			return (1);
		}
		lst = lst->next;
	}
	return (0);
}

char	*ft_match_list(char *str, t_list *lst)
{
	int	len;

	len = ft_strlen(str) + 1;
	while (lst)
	{
		if (ft_strncmp(str, (char *)lst->content, len + 1) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

char	*rpn_pop_ops(t_rpn *rpn)
{
	t_list	*tmp;
	if (rpn->ops)
	{
		tmp = rpn->ops;
		rpn->ops = rpn->ops->next;
		tmp->next = NULL;
		ft_lstadd_back(rpn->out, tmp);
	}
	return (NULL);
}

char	*rpn_popending(t_rpn *rpn)
{
	t_list	*tmp;
	while (rpn->ops)
	{
		if (ft_match_list(rpn->ops->content, rpn->parenthesis))
			return (rpn->ops->content);
		tmp = rpn->ops;
		rpn->ops = rpn->ops->next;
		tmp->next = NULL;
		ft_lstadd_back(rpn->out, tmp);
	}
	return (NULL);
}

char	*rpn_handle_parenthesis(t_rpn *rpn, int i)
{
	char	*parenthesis;

	parenthesis = rpn->current->content;
	if (!ft_strncmp(parenthesis, "(", 2))
		ft_lstaddfront(rpn->ops, ft_lstnew_rpn(")", 0));
	else if (!ft_strncmp(parenthesis, "{", 2))
		ft_lstaddfront(rpn->ops, ft_lstnew_rpn("}", 0));
	else if (!ft_strncmp(parenthesis, ")", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, ")", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (parenthesis);
		else
			rpn_pop_ops(rpn);
	}
	else if (!ft_strncmp(parenthesis, "}", 2))
	{
		while (rpn->ops && ft_strncmp(rpn->ops->content, "}", 2))
			rpn_pop_ops(rpn);
		if (!rpn->ops)
			return (parenthesis);
		else
			rpn_pop_ops(rpn);
	}
	return (NULL);
}

char	*rpn_handle_operators(t_rpn *rpn, int i)
{
	t_list	*op;

	op = rpn->current;
	while (rpn->ops && (op->precedence <= rpn->ops->precedence))
		rpn_pop_ops(rpn);
	ft_lstadd_front(&rpn->ops, ft_lstnew_rpn(op->content, op->precedence));
	return (NULL);
}

char	*rpn_isspecialtreatment(t_rpn *rpn, int i)
{
	char	*special;

	special = ft_match_list(rpn->current->content, rpn->parenthesis);
	if (special)
		return (rpn_handle_parenthesis(rpn, i));
	else
		return (rpn_handle_operators(rpn, i));
}

t_rpn	*get_list(char *str)
{
	int	i;
	int	j;
	t_rpn	*rpn;

	i = 0;
	init_rpn(rpn, str);
	while (rpn->s[i])
	{
		// baser tous les espaces tabs
		while (rpn->s[i] && ft_strchr(rpn->blanks, rpn->s[i]))
			i++;
		j = i;
		// tant que rpn->s[i] n'est pas special, on continue
		while (rpn->s[i] && !rpn_isspecial(&rpn, i))
			i++;
		// on est soit a la fin de rpn->s, soit sur le debut d'un special
		// Si on a atteint la fin de la rpn->s, on depile toute la liste ops dans out
		if (!rpn->s[i])
			rpn_popending(&rpn);
		// Sinon on ajoute le bout de string dans out puis on traite le caractere special
		else
		{
			ft_lstadd_back(&rpn->out, ft_lstnew_rpn(ft_strtrim(ft_strdup(str + j, i), rpn->blanks), 0));
			rpn_isspecialtreatment(&rpn, i);
			i += ft_strlen(rpn->current->content);
		}
	}
	return (rpn);
}

int	main(void)
{
	char str[] = "   {(a|b) && c} || (d || e) || {f | (g || h)}";

	// t_list	*specials = ft_delimiters();
	// printf("%d\n", ft_lstbelongs(delimiters, "|| &&    zczec", &cmp, &len));
	// ft_strdup(str);
	ft_lstprint(get_list(str));
	return (0);
}

/*

7 + (3 * (6 / 3)) * (8 - 4)

1 - 3 + 2 - 4

13-2+4-

7363/*84-*+

7363/*84-*+


712cc -o theaters theaters.c -lcJSON+
31

7832^x
)+
            ||
       &&        ||
	 |    c     d  e
	a b              

a -> | ->
*/
// -> {()aaaaaa}  {({({})})}
//    zsh: parse error near `{'
// comprend pas tb cette erreur




// char	ft_prthsis_pop(t_list	**list)
// {
// 	char	c;
// 	t_list	*pop;

// 	c = 0;
// 	pop = ft_lstpop(list, NULL);
// 	if (pop)
// 	{
// 		c = *(char *)pop->content;
// 		ft_lstclear(&pop, &del);
// 	}
// 	return (c);
// }

// char	parse_parenthesis (char *str)
// {
// 	int		i;
// 	char	c;
// 	t_list	*prthsis;
// 	char	pop;

// 	if (!str)
// 		return (-1);
// 	i = -1;
// 	prthsis = NULL;
// 	while (str[++i])
// 	{
// 		c = str[i]  + (str[i] == '{') + 1;
// 		if (strchr("({", str[i]))
// 			ft_lstadd_front(&prthsis, ft_lstnew(ft_strdup(&c, 1)));
// 		else if (strchr(")}", str[i]))
// 		{
// 			pop = ft_prthsis_pop(&prthsis);
// 			if (!pop || pop != str[i])
// 				break ;
// 		}
// 	}
// 	ft_lstclear(&prthsis, &del);
// 	return (str[i]);
// }