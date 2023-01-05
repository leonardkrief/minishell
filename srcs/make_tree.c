/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/05 07:27:04 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del(void *str)
{
	free(str);
}

int	cmp(void *va, void *vb)
{
	char	*a;
	char	*b;
	size_t	len;

	a = (char *)va;
	b = (char *)vb;
	if (!b)
		return (-1);
	len = ft_strlen(b);
	return (ft_strncmp(a, b, len));
}

int	len(void *vstr)
{
	char	*str;

	str = (char *)vstr;
	if (!str)
		return (-1);
	return (ft_strlen(str));
}

char	ft_prthsis_pop(t_list	**list)
{
	char	c;
	t_list	*pop;

	c = 0;
	pop = ft_lstpop(list, NULL);
	if (pop)
	{
		c = *(char *)pop->content;
		ft_lstclear(&pop, &del);
	}
	return (c);
}

char	parse_parenthesis (char *str)
{
	int		i;
	char	c;
	t_list	*prthsis;
	char	pop;

	if (!str)
		return (-1);
	i = -1;
	prthsis = NULL;
	while (str[++i])
	{
		c = str[i]  + (str[i] == '{') + 1;
		if (strchr("({", str[i]))
			ft_lstadd_front(&prthsis, ft_lstnew(ft_strdup(&c, 1)));
		else if (strchr(")}", str[i]))
		{
			pop = ft_prthsis_pop(&prthsis);
			if (!pop || pop != str[i])
				break ;
		}
	}
	ft_lstclear(&prthsis, &del);
	return (str[i]);
}

t_list	*ft_delimiters(void)
{
	t_list	*delimiters;

	delimiters = NULL;
	ft_lstadd_front(&delimiters, ft_lstnew(ft_strdup("|", -1)));
	ft_lstadd_front(&delimiters, ft_lstnew(ft_strdup(";", -1)));
	ft_lstadd_front(&delimiters, ft_lstnew(ft_strdup("&&", -1)));
	ft_lstadd_front(&delimiters, ft_lstnew(ft_strdup("||", -1)));
	return (delimiters);
}

t_list	*get_list(char *str)
{
	int	i;
	int	j;
	t_list	*delimiters;
	t_list	*list;
	t_list	*del_list;

	delimiters = ft_delimiters();
	i = 0;
	list = NULL;
	del_list = NULL;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '
				|| (str[i] == '(' || str[i] == '{')))
			i++;
		j = i;
		while (str[i] && str[i] != ')' && str[i] != '}' 
			&& !ft_lstbelongs(delimiters, str + i, &cmp, &len))
			i++;
		if (i > j)
			ft_lstadd_front(&list, ft_lstnew(ft_strtrim(ft_strdup(str + j, i - j), " \t")));
		else if (i == j && str[i] && str[i] != ')' && str[i] != '}')
		{
			i += ft_lstbelongs(delimiters, str + i, &cmp, &len);
			ft_lstadd_front(&del_list, ft_lstnew(ft_strtrim(ft_strdup(str + j, i - j), " \t")));
		}
		while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '
				|| (str[i] == ')' || str[i] == '}')))
			i++;
	}
	return (list);
}

int	main(void)
{
	char str[] = "   {  (a|b) && c} || (d || e) )";

	// t_list	*delimiters = ft_delimiters();
	// printf("%d\n", ft_lstbelongs(delimiters, "|| &&    zczec", &cmp, &len));
	// ft_strdup(str);
	ft_lstprint(get_list(str));
	return (0);
}

/*
            ||
       &&        ||
	 |    c     d  e
	a b              

a -> | ->
*/
// -> {()aaaaaa}  {({({})})}
//    zsh: parse error near `{'
// comprend pas tb cette erreur

