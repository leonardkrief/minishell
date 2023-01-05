/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/05 04:54:03 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *str)
{
	free(str);
}

char	ft_prthsis_pop(t_list	**list)
{
	char	c;
	t_list	*pop;

	pop = ft_lstpop(list);
	c = *(char *)pop->content;
	ft_lstclear(&pop, &del);
	return (c);
}

char	parse_parenthesis (char *str)
{
	int		i;
	char	c[2];
	t_list	*prthsis;
	char	pop;

	if (!str)
		return (-1);
	i = -1;
	c[1] = '\0';
	prthsis = NULL;
	while (str[++i])
	{
		c[0] = str[i]  + (str[i] == '{') + 1;
		if (strchr("({", str[i]))
			ft_lstadd_front(&prthsis, ft_lstnew(ft_strdup(c)));
		else if (strchr(")}", str[i]))
		{
			pop = ft_prthsis_pop(&prthsis);
			if (!pop || pop != str[i])
				break ;
		}
		ft_lstprint(prthsis);
	}
	ft_lstclear(&prthsis, &del);
	return (str[i]);
}

int	main(void)
{
	char str[] = " {()aaaaaa}  {({({})}))}";

	printf("%d\n", parse_parenthesis(str));
	return (0);
}

// t_btree	*get_tree(char *str)
// {
// 	int		parens;
// 	int		bracks;
// 	t_btree	*t;

// 	parens = 0;
// 	bracks = 0;
// 	t = NULL;
// }

// -> {()aaaaaa}  {({({})})}
//    zsh: parse error near `{'
// comprend pas tb cette erreur