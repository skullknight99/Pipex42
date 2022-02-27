BSRCS	= pipex_bonus.c utils_bonus.c pipex_utils.c
SRCS	= pipex.c pipex_utils.c
NAME	= pipex
CC	= gcc
FLAGS	= -Wall  -Werror -Wextra 
RM	= rm -f
INCS	= libft/includes
LIBFT	= -Llibft -lft

all: ${NAME}

${NAME}: runlibft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

ignore: runlibft
	${CC} ${FLAGS} -o ${NAME} ${SRCS} -I ${INCS} ${LIBFT}

bonus: runlibft norm
	${CC} ${FLAGS} -o ${NAME} ${BSRCS} -I ${INCS} ${LIBFT}

clean:
	find . -name "*.o" -delete

fclean: clean
	${RM} ${NAME}
	make -C libft fclean

re: fclean all

test:
	$(CC) main.c -I ${INCS} ${LIBFT}

runlibft:
	make -C libft

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS} ${BSRCS}
	norminette -R CheckDefine ${INCS} pipex.h pipex_bonus.h

.PHONY: all re clean fclean