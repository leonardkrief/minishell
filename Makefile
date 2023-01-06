SRCS		=	srcs/rpn/rpn_algo.c \
				srcs/rpn/rpn_basics.c \
				srcs/rpn/rpn_pop_utils.c \
				srcs/rpn/rpn_utils.c \
				srcs/trees/make_tree.c \
				srcs/trees/trees.c \
				srcs/trees/print_tree/print_trees.c \
				srcs/trees/print_tree/queues.c \
				srcs/main.c


OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP -g3
INCLUDE		=	-Iinclude -Ilibft
EXECUTION	=	execution
LIBS		=	libft/libft.a
RM			=	rm -rf

${EXECUTION}:	${OBJS}
				make -C libft
				${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${EXECUTION}

all:	${EXECUTION}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}


bonus:	${EXECUTION}

clean:
		${RM} ${OBJS}
		${RM} ${DEPS}

fclean:	clean
		${RM} ${EXECUTION}

ffclean:	fclean
			make fclean -C libft

re:		fclean all

-include : ${DEPS}

.PHONY: all clean fclean re
