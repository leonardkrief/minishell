#ifndef MINISHELL_H
# define MINISHELL_H

# include "minishell_structs.h"

// print_trees.c
t_queue	*new_queue(void *data, int id);
void	add_queue(t_queue **queue, t_queue *add);
t_btree	*pop(t_queue **trees);
void	print_queue(t_queue *q);
void	get_print_tree(t_queue **trees, t_queue **to_print);
int	get_local_depth(t_queue *to_print);
int	get_depth(t_queue *to_print);
void	print_print(t_queue *to_print, int node_size);
void	print_tree(t_btree *t, int node_size);

// trees.c
t_btree	*new_node(void *node);
void	add_left(t_btree **tree, t_btree *left_son);
void	add_right(t_btree **tree, t_btree *right_son);
void	free_tree(t_btree *t);

#endif