SRCS		=	srcs/make_tree.c \
				srcs/trees.c \

OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -MMD -MP
INCLUDE		=	-Iinclude
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
