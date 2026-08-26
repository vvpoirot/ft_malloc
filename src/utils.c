#include "ft_malloc.h"

void *use_mmap(size_t size) {
	void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	return (ptr);
}

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
	new_block = use_mmap(zone_size);

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
	void 	*zone_end;
	void 	*zone_start;
	t_block *block = *target_block;

	if (zone_size == ZONE_TINY) {
		zone_start = (void *)g_heap.tiny_alloc;
		while ((void *)block >= zone_start + ZONE_TINY)
			zone_start += ZONE_TINY;
		zone_end = zone_start + ZONE_TINY;
	} else if (zone_size == ZONE_SMALL) {
		zone_start = (void *)g_heap.small_alloc;
		while ((void *)block >= zone_start + ZONE_SMALL)
			zone_start += ZONE_SMALL;
		zone_end = zone_start + ZONE_SMALL;
	}

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
