#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"

# define MALLOC_FAILED	0b00000000000000000000001

# define NULL_ERROR		0b10000000000000000000000


typedef struct s_btree{
	void			*node;
	struct s_btree	*r;
	struct s_btree	*l;
}	t_btree;

typedef struct s_queue{
	void			*data;
	int				id;
	struct s_queue	*next;
}	t_queue;


// to free : out, ops, parenthesis, operators, specials
typedef struct s_rpn{
	t_list	*out;
	t_list	*ops;
	t_list	*parenthesis;
	t_list	*operators;
	t_list	*specials;
	char	*blanks;
	char	*s;
	t_list	*current;
}	t_rpn;

#endif