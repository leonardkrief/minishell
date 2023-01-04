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


#endif