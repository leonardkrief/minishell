/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 03:53:52 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 05:09:45 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	//char str[] = "   {(a|b) && c} || (d || e) || {f | (g || h)}";
	//char str[] = "  {(true|false) && false} )|| (true || false) ";
	char	*str;
	t_btree	*tree;

	// t_list	*specials = ft_delimiters();
	// printf("%d\n", ft_lstbelongs(delimiters, "|| &&    zczec", &cmp, &len));
	// ft_strdup(str);
	str = NULL;
	if (ac >= 2)
		str = av[1];
	
	tree = get_tree(str);
	if (tree)
		print_tree(tree, 2);
	return (0);
}

/*

7 + (3 * (6 / 3)) * (8 - 4)

1 - 3 + 2 - 4

13-2+4-

// {(a|b) && c} || (d || e) || {f | (g || h)}
// a b | c && d e || || f g h || |
// a b | c && d e || || f g h || | ||
((a | b) && c) || (d || e)
{(true|true) && true} || (false || false) && || {true | (false || false)}
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
// -> {()}
//    zsh: parse error near `{'
// 					comprend pas tb cette erreur
// -> {(())}
// 					ne renvoie pas d'erreur 
// -> ({})
// 					ne renvoie pas d'erreur non plus 




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