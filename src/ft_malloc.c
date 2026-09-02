#include "../includes/ft_malloc.h"

t_heap g_heap;

void* malloc(size_t size) {
	// ft_putstr("MY MALLOC\n", ft_strlen("MY MALLOC\n"));
	// ft_putnbr_fd(size, 1);
	// write(1, "\n", 1);
	size_t alignee_size = ALIGN(size);

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

		return ((char *)block + HEADER_SIZE);

	}
	else {
		size_t large_alignee_size = ALIGN(size) + HEADER_SIZE;
		size_t mmap_size = (large_alignee_size + (PAGESIZE - 1)) & ~(PAGESIZE - 1);

		t_block *new_block = use_mmap(mmap_size);
		if (!new_block || new_block == MAP_FAILED) {
			write(2, "LARGE FAILED\n", 13);
			return (NULL);
		}
		new_block->size = mmap_size - HEADER_SIZE;
		new_block->is_free = NOTFREE;

		g_heap.large_alloc = add_block(g_heap.large_alloc, new_block);

		return ((char *)new_block + HEADER_SIZE);
	}
	return (NULL);
}
