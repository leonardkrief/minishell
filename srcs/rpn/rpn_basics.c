/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_basics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/08 03:12:53 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_rpn(t_rpn *rpn, char *to_parse)
{
	ft_memset(rpn, 0, sizeof(*rpn));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strndup(")", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strndup("(", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strndup("{", -1), 0));
	ft_lstadd_front(&rpn->parenthesis, ft_lstnew_rpn(ft_strndup("}", -1), 0));
	//ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strndup("|", -1), 1));
	ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strndup("&&", -1), 1));
	ft_lstadd_front(&rpn->operators, ft_lstnew_rpn(ft_strndup("||", -1), 1));
	ft_lstappendcopy(&rpn->specials, rpn->operators);
	ft_lstappendcopy(&rpn->specials, rpn->parenthesis);
	rpn->blanks = ft_strndup("\t ", 2);
	rpn->s = to_parse;
}

void	free_rpn(t_rpn *rpn)
{
	//out, ops, parenthesis, operators, specials
	ft_lstclear(&rpn->out, &free);
	ft_lstclear(&rpn->ops, &free);
	ft_lstclear(&rpn->parenthesis, &free);
	ft_lstclear(&rpn->operators, &free);
	ft_lstclear(&rpn->specials, &free);
}

char	*invert_quotes(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				s[i++] *= -1;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				s[i++] *= -1;
		}
		i++;
	}
	return (s);
}

t_rpn	*rpn(t_rpn *rpn, char *str)
{
	if (str == NULL)
		return (NULL);
	else
	{
		invert_quotes(str);
		generate_rpn(rpn, str);
		return (rpn);
	}
}
