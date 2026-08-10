#include "ft_malloc.h"

void* ft_malloc(size_t size) {
	size_t alignee_size = ALIGN(size);
	if (alignee_size <= TINY) {
		
		t_block *block_a;

		int blocklen = ft_blocksize(g_heap.tiny_alloc);
		if (!blocklen) {
			block_a = private_mmap(TINY);
			if (!block_a) return (NULL);
			return ((char *)block_a + HEADER_SIZE);
		}

		ft_printf("%s // %d\n", "TINY", blocklen);
	}
	else if (alignee_size <= SMALL) {
		ft_printf("%s // %d\n", "SMALL", alignee_size);
	}
	else {
		ft_printf("%s // %d\n", "LARGE", alignee_size);
	}
	return (NULL);
}
