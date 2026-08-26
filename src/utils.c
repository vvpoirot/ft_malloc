#include "ft_malloc.h"

t_block *get_available_block(t_block *start, size_t req_size) {
	t_block *current = start;

	while (current) {
		if (current->is_free == FREE && current->size >= req_size)
			return (current);
		current = current->next;
	}

	return (NULL);
}

void split_in_new_block(t_block **block, size_t size) {
	t_block *new;
	t_block *current;
	size_t old_current_size;

	current = *block;

	old_current_size = current->size;
	current->size = size;

	new = (t_block *)((char *)current + HEADER_SIZE + current->size);
	new->size = old_current_size - current->size - HEADER_SIZE;
	new->is_free = FREE;

	new->next = current->next;
	new->prev = current;
	current->next = new;

	*block = current;
}

size_t	alloc_new_block(size_t zone_size, t_block **block) {
	t_block *new_block;

	new_block = *block;
	new_block = mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (!new_block || new_block == MAP_FAILED)
		return (0);

	new_block->is_free = FREE;
	new_block->size = zone_size - HEADER_SIZE;

	*block = new_block;

	return (zone_size);
}

t_block *add_block(t_block *list, t_block *block) {
	if (!list)
		return (block);
	t_block *last = list;
	while (last->next)
		last = last->next;
	last->next = block;
	block->prev = last;
	return (list);
}

bool	merge_block(size_t zone_size, t_block **target_block) {
	t_block *block = *target_block;
	void 	*zone_start = (void *)((uintptr_t)block & ~(zone_size- 1));
	void 	*zone_end = (char *)zone_start + zone_size;

	while (block->next && (void *)block->next < zone_end && block->next->is_free == FREE) {
		block->size += HEADER_SIZE + block->next->size;
		block->next = block->next->next;
		if (block->next)
			block->next->prev = block;
	}

	while (block->prev && (void *)block->prev >= zone_start && block->prev->is_free == FREE) {
		block->prev->size += HEADER_SIZE + block->size;
		block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		block = block->prev;
	}

	*target_block = block;

	if (block->size == zone_size - HEADER_SIZE) {
		if (block->prev)
            block->prev->next = block->next;
        else {
            if (zone_size == ZONE_TINY)
                g_heap.tiny_alloc = block->next;
            else if (zone_size == ZONE_SMALL)
                g_heap.small_alloc = block->next;
        }
        if (block->next)
            block->next->prev = block->prev;

        return (false);
	}
	return (true);
}
