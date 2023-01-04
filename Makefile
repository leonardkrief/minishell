SRCS		=	srcs/print_trees.c \
				srcs/trees.c \
				srcs/main.c

OBJS		= $(SRCS:.c=.o)
DEPS		= $(SRCS:.c=.d)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3
INCLUDE		=	-Iinclude
EXECUTION	=	execution
RM			=	rm -rf

all:	${EXECUTION}

.c.o:
		${CC} ${CFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}

${EXECUTION}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBS} -o ${EXECUTION}

bonus:	${EXECUTION}

clean:
		${RM} ${OBJS}
		${RM} ${DEPS}

fclean:	clean
		${RM} ${EXECUTION}

re:		fclean all

-include : ${DEPS}

.PHONY: all clean fclean re
.SILENT:
