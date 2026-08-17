LIBFT = ./libft/libft.a

PROJECT_NAME = ft_malloc

NAME = ${PROJECT_NAME}.a

SRC = src/main.c\
		src/utils.c\
		src/ft_malloc.c\
		src/show_alloc_mem.c\
		src/ft_free.c\

OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror

CC = @cc ${CFLAGS}

all: ${NAME} ${OBJ}

$(NAME): ${OBJ}
	@printf "Loading\r"
	@${MAKE} -C ./libft
	@cp libft/libft.a ${NAME}
	@ar rc ${NAME} ${OBJ}
	@${CC} ${SRC} ${LIBFT} -o ${PROJECT_NAME}
	@printf "Finish !\n"

clean:
	@${MAKE} clean -C ./libft
	@rm -f src/*.o

fclean: clean
	@${MAKE} fclean -C ./libft
	@rm -f ${NAME}
	@rm -f ${PROJECT_NAME}
	@printf "Delete files !\n"

re: fclean all