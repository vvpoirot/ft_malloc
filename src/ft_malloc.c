#include "ft_malloc.h"

t_heap g_heap;

void* ft_malloc(size_t size) {
	size_t alignee_size = ALIGN(size);
	ft_printf("%d // %d\n", ZONE_TINY, ZONE_SMALL);

	if (alignee_size <= TINY) {
		
		t_block *block;

		block = get_available_block(g_heap.tiny_alloc, alignee_size);
		if (!block) {

			size_t zone_size = alloc_new_block(ZONE_TINY, &block);
			if (!zone_size)
				return (NULL);

			g_heap.tiny_alloc = add_block(g_heap.tiny_alloc, block);

		}
		block->is_free = NOTFREE;
		split_in_new_block(&block, alignee_size); 
		// printf("%zu // %zu // %d \n", block->size, block->next->size, block->next->is_free);

		return ((char *)block + HEADER_SIZE);

	}
	else if (alignee_size <= SMALL) {

		t_block *block;

		block = get_available_block(g_heap.small_alloc, alignee_size);
		if (!block) {

			size_t zone_size = alloc_new_block(ZONE_SMALL, &block);
			if (!zone_size)
				return (NULL);

			g_heap.small_alloc = add_block(g_heap.small_alloc, block);

		}
		block->is_free = NOTFREE;
		split_in_new_block(&block, alignee_size); 
		// printf("%zu // %zu // %d \n", block->size, block->next->size, block->next->is_free);

		return ((char *)block + HEADER_SIZE);

	}
	else {
		size_t large_alignee_size = ALIGN(size) + HEADER_SIZE;
		size_t mmap_size = (large_alignee_size + (PAGESIZE - 1)) & ~(PAGESIZE - 1);

		t_block *new_block = mmap(0, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (!new_block || new_block == MAP_FAILED)
			return (NULL);
		new_block->size = mmap_size - HEADER_SIZE;
		new_block->is_free = NOTFREE;

		g_heap.large_alloc = add_block(g_heap.large_alloc, new_block);

		return (new_block);
	}
	return (NULL);
}
