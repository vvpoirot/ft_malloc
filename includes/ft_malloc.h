#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <sys/mman.h>
# include <unistd.h> // for sysconf

// temp
# include <stdint.h>
# include <stdbool.h>

# define FREE 1
# define NOTFREE 0

# define PAGESIZE sysconf(_SC_PAGESIZE)
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

extern t_heap g_heap;

# define HEADER_SIZE ALIGN(sizeof(t_block))

# define TINY 128 // n (1 to n)
# define SMALL 1024 // m (n + 1 to m)
# define ZONE_TINY (32 * 1024) // N
# define ZONE_SMALL (128 * 1024) // M
 
// main functions
void		show_alloc_mem();
void 		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

// utils functions
void 		*use_mmap(size_t size);
t_block 	*add_block(t_block *list, t_block *block);
void		split_in_new_block(t_block **block, size_t size);
size_t		alloc_new_block(size_t zone_size, t_block **block);
bool		merge_block(size_t zone_size, t_block **target_block);
t_block 	*get_available_block(t_block *start, size_t req_size);

#endif