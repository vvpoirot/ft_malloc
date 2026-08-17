#include "ft_malloc.h"

void show_alloc_mem() {
	t_block *tiny = g_heap.tiny_alloc;
	t_block *small = g_heap.small_alloc;
	t_block *large = g_heap.large_alloc;

	ft_printf("TINY : %p\n", (void *)tiny);
	while (tiny) {
		if (tiny->is_free == NOTFREE)
			ft_printf("%p - %p : %d\n", (void *)((char *)tiny + HEADER_SIZE), (void *)((char *)tiny + HEADER_SIZE + tiny->size), tiny->size);
		tiny = tiny->next;
	}

	ft_printf("SMALL : %p\n", (void *)small);
	while (small) {
		if (small->is_free == NOTFREE)
			ft_printf("%p - %p : %d\n", (void *)((char *)small + HEADER_SIZE), (void *)((char *)small + HEADER_SIZE + small->size), small->size);
		small = small->next;
	}

	ft_printf("LARGE : %p\n", (void *)large);
	while (large) {
		if (large->is_free == NOTFREE)
			ft_printf("%p - %p : %d\n", (void *)((char *)large + HEADER_SIZE), (void *)((char *)large + HEADER_SIZE + large->size), large->size);
		large = large->next;
	}

}
