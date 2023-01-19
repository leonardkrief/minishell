#ifndef MINITREES_STRUCTS_H
# define MINITREES_STRUCTS_H

# include "../liblkriefft/liblkriefft.h"
# include <limits.h>
# include <math.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FAILED_MALLOC			0b00000000000000000000001

# define ERROR_EXPRESSION		0b00000000000000000000010
# define ERROR_RPN				0b00000000000000000000100
# define ERROR_RPN_PARSING		0b00000000000000000001000
# define ERROR_NULL				0b10000000000000000000000

typedef struct s_data t_data;

typedef struct s_btree
{
	void			*node;
	t_data			*data;
	struct s_btree	*r;
	struct s_btree	*l;
}					t_btree;

typedef struct s_data
{
	int				prev_pipes;
	pid_t			pid[1024];
	char			**env;
	char			**path;
	char			**split;
	int				fd[2];
	int				status;

	char			*prompt;
}					t_data;

typedef struct s_queue
{
	void			*data;
	int				id;
	struct s_queue	*next;
}					t_queue;

typedef	struct	s_rr
{
	char		*content;
	int			type;
	struct s_rr	*next;
}				t_rr;

typedef struct s_cmd
{
	char		*cmd;
	char		*flags;
	t_rr		*redi;
}					t_cmd;

typedef struct s_rpn
{
	t_list			*out;
	t_list			*ops;
	t_list			*parenthesis;
	t_list			*operators;
	t_list			*specials;
	char			*blanks;
	char			*s;
	t_list			*prev;
	t_list			*current;
}					t_rpn;

#endif
