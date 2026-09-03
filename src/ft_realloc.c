#include "../includes/ft_malloc.h"

static bool same_zone(size_t new, size_t current);
static bool in_mmap_zone(t_block* block);

void	*realloc(void *ptr, size_t size) {
	t_block *block;

	if (!ptr)
		return (malloc(size));
	else if (size == 0) {
		free(ptr);
		return (NULL);
	}

	size_t alignee_size = ALIGN(size);

	block = (t_block *)((char *)ptr - HEADER_SIZE);

	if (in_mmap_zone(block) && same_zone(alignee_size, block->size) && block->next->is_free == FREE && (block->next->size + block->size + HEADER_SIZE) >= alignee_size)
	{
		size_t old_size = block->size;
		size_t old_next_size = block->next->size;

		t_block *new_next_block = (t_block *)((char *)block + HEADER_SIZE + alignee_size);
		new_next_block->is_free = FREE;
		new_next_block->size = (old_size + old_next_size) - alignee_size;
		new_next_block->next = block->next->next;
		new_next_block->prev = block;

		block->size = alignee_size;
		block->next = new_next_block;
		if (new_next_block->next)
			new_next_block->next->prev = new_next_block;

		return ((char *)block + HEADER_SIZE);
	}
	else
	{
		void* new_pointer;

		new_pointer = malloc(alignee_size);
		if (!new_pointer)
			return (NULL);

		size_t copy_size = (block->size < alignee_size) ? block->size : alignee_size;
		ft_memcpy(new_pointer, ptr, copy_size);
		free(ptr);

		return (new_pointer);
	}

	return (NULL);
}

static bool in_mmap_zone(t_block* block) {
	size_t zone_size;

	if (block->size <= TINY)
		zone_size = ZONE_TINY;
	else if (block->size <= SMALL)
		zone_size = ZONE_SMALL;
	else
		return (false);

	void 	*zone_start = (void *)((uintptr_t)block & ~(zone_size- 1));
	void 	*zone_end = (char *)zone_start + zone_size;

	return (block->next && (void *)block->next < zone_end && (void *)block->next >= zone_start);
}

static bool same_zone(size_t new, size_t current) {
	if (new <= TINY && current <= TINY)
		return (true);
	if (new <= SMALL && current <= SMALL && current >= TINY && new >= TINY)
		return (true);
	return (false);
}

/*
typedef struct s_handler {
    size_t      max_size;
    void        (*func)(t_block *);
} t_handler;

static const t_handler handlers[] = {
    { TINY,  handle_tiny },
    { SMALL, handle_small },
    { 0,     handle_large } // Fallback / Défaut
};

void process_block(t_block *b) {
    for (int i = 0; handlers[i].func; i++) {
        if (b->size <= handlers[i].max_size || handlers[i].max_size == 0) {
            handlers[i].func(b);
            return;
        }
    }
}
*/
