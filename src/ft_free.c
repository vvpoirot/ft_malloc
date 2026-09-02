#include "../includes/ft_malloc.h"

void free(void *ptr) {
	t_block *block;

	if (!ptr)
		return ;

	block = (t_block *)((char *)ptr - HEADER_SIZE);
	block->is_free = FREE;

	if (block->size <= TINY) {
		if (!merge_block(ZONE_TINY, &block))
			munmap((void *)block, ZONE_TINY);
	}
	else if (block->size <= SMALL) {
		if (!merge_block(ZONE_SMALL, &block))
			munmap((void *)block, ZONE_SMALL);
	}
	else {
		if (block->prev)
			block->prev->next = block->next;
		else
			g_heap.large_alloc = block->next;

		if (block->next)
			block->next->prev = block->prev;

		size_t total_size = HEADER_SIZE + block->size;
		munmap((void *)block, total_size);
		return;	
	}

}
