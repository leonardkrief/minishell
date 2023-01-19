/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rpn_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/19 16:30:28 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew_rpn(void *content, int precedence)
{
	t_list	*new;
	// if (content = NULL)
		//return (error_handler(t_rpn *rpn, NULL_FAILURE));
	if (!content)
		return (NULL);
	new = ft_lstnew(content);
	if (!new)
	{
		free(content);
		return (ft_puterror(FAILED_MALLOC, (char *)"ft_lstnew_rpn"));
	}
	new->precedence = precedence;
	return (new);
}

void	*ft_lstappendcopy(t_list **lst, t_list *copy)
{
	t_list	*new;

	while (copy)
	{
		new = ft_lstnew_rpn(ft_strndup(copy->content, -1), copy->precedence);
		if (!new)
			return (ft_puterror(FAILED_MALLOC, (char *)"ft_lstappendcopy"));
		ft_lstadd_back(lst, new);
		copy = copy->next;
	}
	return (new);
}

// checks if str exists in one of lst contents
char	*ft_match_list(char *str, t_list *lst)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str) + 1;
	while (lst)
	{
		if (!ft_strncmp(str, (char *)lst->content, len + 1))
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

int	is_a_closed_parenthesis(char *str)
{
	if (!ft_strncmp(str, ")", 2))
		return (1);
	return (0);
}
