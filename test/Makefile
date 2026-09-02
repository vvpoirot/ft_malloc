CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFLAGS = -I../includes -L../libft -lft -L.. -lft_malloc

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
INC_DIR = ../includes
LIB_DIR = ..

TEST1 = test1
TEST2 = test2

all: init test1 test2 real

init:
	@$(MAKE) -C ../

# --------------------------------------------------
# TEST 1
# --------------------------------------------------

test1: test1.c
	@echo "\n========================================\n"
	@echo " Compiling test1\n"
	@echo "========================================\n"
	@$(CC) $(CFLAGS) $< -o $@
	@echo "\n--- Running test1 WITHOUT libft_malloc ---\n"
	@./$(TEST1)
	@echo "\n--- Running test1 WITH libft_malloc ---\n"
	@LD_PRELOAD=$(LIB_DIR)/libft_malloc.so ./$(TEST1)

# --------------------------------------------------
# TEST 2
# --------------------------------------------------

test2: test2.c $(LIBFT) $(LIB_DIR)/libft_malloc.so
	@echo "\n========================================\n"
	@echo " Compiling test2\n"
	@echo "========================================\n"
	@$(CC) $(CFLAGS) $< $(LIBFLAGS) -o $@
	@echo "\n--- Running test2 ---\n"
	@LD_LIBRARY_PATH=$(LIB_DIR) ./$(TEST2)

# --------------------------------------------------
# REAL COMMANDS
# --------------------------------------------------

real:
	@echo "\n========================================\n"
	@echo " REAL COMMANDS TEST\n"
	@echo "========================================\n"

	@echo "\n--- ls WITHOUT libft_malloc ---\n"
	@ls

	@echo "\n--- ls WITH libft_malloc ---\n"
	@LD_PRELOAD=$(LIB_DIR)/libft_malloc.so ls

	@echo "\n--- echo WITHOUT libft_malloc ---\n"
	@echo "Hello from system malloc"

	@echo "\n--- echo WITH libft_malloc ---\n"
	@LD_PRELOAD=$(LIB_DIR)/libft_malloc.so echo "Hello from my malloc"

	@echo "\n--- pwd WITHOUT libft_malloc ---\n"
	@pwd

	@echo "\n--- pwd WITH libft_malloc ---\n"
	@LD_PRELOAD=$(LIB_DIR)/libft_malloc.so pwd

# --------------------------------------------------
# LIBFT
# --------------------------------------------------

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

# --------------------------------------------------
# CLEAN
# --------------------------------------------------

clean:
	@rm -f $(TEST1) $(TEST2)
	@$(MAKE) -C ../ clean

fclean: clean
	@$(MAKE) -C ../ fclean

re: fclean all

.PHONY: all test1 test2 real clean fclean re