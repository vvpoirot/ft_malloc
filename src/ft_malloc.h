#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <sys/mman.h>
# include <unistd.h> // for sysconf

# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))

typedef struct s_block {
	size_t	size;
	int		is_free;
	struct s_block *next;
	struct s_block *prev;
}	t_block;

typedef struct s_heap {
	t_block *tiny_alloc;
	t_block *small_alloc;
	t_block *large_alloc;
}	t_heap;

static t_heap g_heap;

# define HEADER_SIZE ALIGN(sizeof(t_block))

# define TINY 128 // n (1 to n)
# define SMALL 1024 // m (n + 1 to m)
# define ZONE_TINY (100 * (TINY + HEADER_SIZE)) // N
# define ZONE_SMALL (100 * (SMALL + HEADER_SIZE)) // M

// main functions
void*	ft_malloc(size_t size);

// utils functions
int		ft_blocksize(t_block *block);
void*	private_mmap(size_t zone_size);

#endif