#include "ft_malloc.h"

static bool same_zone(size_t new, size_t current);
static bool in_mmap_zone(t_block* block, size_t zone_size);

void	*ft_realloc(void *ptr, size_t size) {
	t_block *block;

	if (!ptr)
		return(NULL);
	size_t alignee_size = ALIGN(size);

	block = (t_block *)((char *)ptr - HEADER_SIZE);

	// /!\ NE PAS LINK SI LE BLOCK SUIVANT APPARTIENS A UN AUTRE MMAP SINON CRASH AU NIVEAU DE FREE
	if (in_mmap_zone(block, ZONE_TINY) && same_zone(alignee_size, block->size) && block->next->is_free == FREE && (block->next->size + block->size + HEADER_SIZE) >= alignee_size)
	{
		ft_printf("Hello World !\n");
	}
	else
	{
		void* new_pointer;

		new_pointer = ft_malloc(alignee_size);
		new_pointer = ft_memcpy(new_pointer, ptr, alignee_size);
		ft_free(ptr);

		return (new_pointer);
	}

	return (NULL);
}

static bool in_mmap_zone(t_block* block, size_t zone_size) {
	void 	*zone_start = (void *)((uintptr_t)block & ~(zone_size- 1));
	void 	*zone_end = (char *)zone_start + zone_size;
	if (block && (void *)block < zone_end && (void *)block >= zone_start)
		return (true);
	return (false);
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
