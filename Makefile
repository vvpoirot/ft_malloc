# CONFIG :

ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so
LINK		= libft_malloc.so

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC			= src/utils.c \
			  src/ft_malloc.c \
			  src/show_alloc_mem.c \
			  src/ft_free.c \
			  src/ft_realloc.c

OBJ			= $(SRC:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -fPIC
LDFLAGS		= -shared

# RULES :

all: $(NAME) $(LINK)

$(NAME): $(OBJ) $(LIBFT)
	@printf "Linking $(NAME)...\n"
	@$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBFT)

$(LIBFT):
	@printf "Compiling libft...\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(LINK): $(NAME)
	@ln -sf $(NAME) $(LINK)
	@printf "$(LINK) -> $(NAME)\n"

%.o: %.c
	@printf "Compiling $<...\n"
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJ)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(LINK)

re: fclean all

.PHONY: all clean fclean re