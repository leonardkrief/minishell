/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_trees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:54:00 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/04 23:32:50 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	*new_queue(void *data, int id)
{
	t_queue *q;

	q = malloc (sizeof(*q));
	if (!q)
		return (NULL);
	q->data = data;
	q->id = id;
	return (q);
}

void	add_queue(t_queue **queue, t_queue *add)
{
	t_queue *q;

	q = *queue;
	if (!q)
		*queue = add;
	else
	{
		while (q->next)
			q = q->next;
		q->next = add;
	}
}

t_btree	*pop(t_queue **trees)
{
	t_btree	*t;

	t = ((t_btree *)(*trees)->data);
	*trees = (*trees)->next;
	return (t);
}

void	print_queue(t_queue *q)
{
	while(q)
	{
		printf("(%d) %s\n", q->id, (char *)q->data);
		q = q->next;
	}
	printf("\n");
}

void	get_print_tree(t_queue **trees, t_queue **to_print)
{
	int		id;
	t_btree	*t;

	if (*trees)
	{
		id = (*trees)->id;
		t = pop(trees);
		add_queue(to_print, new_queue(t->node, id));
		if (t->l)
			add_queue(trees, new_queue(t->l, 2*id));
		if (t->r)
			add_queue(trees, new_queue(t->r, 2*id + 1));
		get_print_tree(trees, to_print);
	}
}

int	get_local_depth(t_queue *to_print)
{
	int	depth;
	int	id;

	id = to_print->id;
	depth = 0;
	while (id > 1)
	{
		id /= 2;
		depth++;
	}
	return (depth);
}

int	get_depth(t_queue *to_print)
{
	while (to_print && to_print->next)
		to_print = to_print->next;
	return (get_local_depth(to_print));
}

void	print_print(t_queue *to_print, int node_size)
{
	int	depth;
	int	local_depth;
	int	id_to_print;
	int	n;

	depth = get_depth(to_print);
	id_to_print = 1;
	while (to_print)
	{
		if (to_print->id == id_to_print)
			local_depth = get_local_depth(to_print);
		printf("%*s", node_size * ((int)pow(2, depth - local_depth) - 1), "");
		if (to_print->id == id_to_print)
		{
			n = printf("%.*s", node_size, (char *)to_print->data);
			if (n < node_size)
				printf("%.*s", node_size - n, "__________");
			to_print = to_print->next;
		}
		else
			printf("%.*s", node_size, "__________");
		printf("%*s", node_size * (int)pow(2, depth - local_depth), "");
		id_to_print++;
		if (id_to_print >= pow(2, local_depth + 1))
			printf("\n");
	}
	printf("\n");
}

void	print_tree(t_btree *t, int node_size)
{
	t_queue *trees;
	t_queue *to_print;

	trees = new_queue((t_btree *)t, 1);
	to_print = NULL;
	get_print_tree(&trees, &to_print);
	print_print(to_print, node_size);
	// print_queue(to_print);
}



//                              01                              
//              02                              03              
//      04              05              06              07      
//  08      09      10      11      12      13      14      15  
//16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31

//                           ---                           
//               ---                     ---               
//         ---         ---         ---         ---         
//   ---         ---         ---         ---         ---   
//---   ---   ---   ---   ---   ---   ---   ---   ---   ---

//                              |_                                $
//              ||                              &&                $
//      &&              d_              e_              f_        $
//  |_      c_    __  __  __  __  __  __  a_  b_  $
