#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include "../libft/libft.h"
# include <sys/mman.h>
# include <unistd.h> // for sysconf

// temp
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>

# define FREE 1
# define NOTFREE 0

# define PAGESIZE sysconf(_SC_PAGESIZE)
# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define ALIGN_TO_PAGE(zone_size) (((zone_size / PAGESIZE) + 1) * PAGESIZE)

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
# define ZONE_TINY ALIGN_TO_PAGE((100 * (TINY + HEADER_SIZE))) // N
# define ZONE_SMALL ALIGN_TO_PAGE((100 * (SMALL + HEADER_SIZE))) // M
 
// main functions
void		show_alloc_mem();
void 		ft_free(void *ptr);
void		*ft_malloc(size_t size);
void		*ft_realloc(void *ptr, size_t size);

// utils functions
t_block 	*add_block(t_block *list, t_block *block);
void		split_in_new_block(t_block **block, size_t size);
size_t		alloc_new_block(size_t zone_size, t_block **block);
bool		merge_block(size_t zone_size, t_block **target_block);
t_block 	*get_available_block(t_block *start, size_t req_size);

#endif