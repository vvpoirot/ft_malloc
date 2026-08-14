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
