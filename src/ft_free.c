#include "ft_malloc.h"

void ft_free(void *ptr) {
	t_block *block;

	if (!ptr)
		return ;

	block = (t_block *)((char *)ptr - HEADER_SIZE);

	block->is_free = FREE;

	void	*zone_start; // uintptr_t automatically matches the pointer size (64-bit on x86_64/ARM64, 32-bit on x86)
	if (block->size <= TINY) {
		if (!merge_block(ZONE_TINY, &block)) {
			zone_start = (void *)((uintptr_t)block & ~(ZONE_TINY- 1));
			munmap(zone_start, ZONE_TINY);
		}
	}
	else if (block->size <= SMALL) {
		if (!merge_block(ZONE_SMALL, &block)) {
			zone_start = (void *)((uintptr_t)block & ~(ZONE_SMALL- 1));
			munmap(zone_start, ZONE_SMALL);
		}
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
