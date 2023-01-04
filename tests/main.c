/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:17:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/04 23:32:50 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_btree	*t;
	char	*a = "a";
	char	*b = "b";
	char	*c = "c";
	char	*d = "d";
	char	*e = "e";
	char	*f = "f";
	char	*pipe = "|";
	char	*dpipe = "||";
	char	*and = "&&";

	t = new_node((char *)pipe);
	t->l = new_node((char *)dpipe);
	t->l->l = new_node((char *)and);
	t->l->l->l = new_node((char *)pipe);
	t->l->l->l->l = new_node((char *)a);
	t->l->l->l->r = new_node((char *)b);
	t->l->l->r = new_node((char *)c);
	t->l->r = new_node((char *)d);
	t->r = new_node((char *)and);
	t->r->l = new_node((char *)e);
	t->r->r = new_node((char *)f);

	print_tree(t, 2);
	return (0);
}