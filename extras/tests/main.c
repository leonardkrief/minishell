/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:17:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/06 04:24:00 by lkrief           ###   ########.fr       */
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

	t = new_tree((char *)pipe);
	t->l = new_tree((char *)dpipe);
	t->l->l = new_tree((char *)and);
	t->l->l->l = new_tree((char *)pipe);
	t->l->l->l->l = new_tree((char *)a);
	t->l->l->l->r = new_tree((char *)b);
	t->l->l->r = new_tree((char *)c);
	t->l->r = new_tree((char *)d);
	t->r = new_tree((char *)and);
	t->r->l = new_tree((char *)e);
	t->r->r = new_tree((char *)f);

	print_tree(t, 2);
	return (0);
}