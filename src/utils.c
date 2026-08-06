#include "ft_malloc.h"

void* private_mmap(size_t zone_size) {
	size_t page_size;

	page_size = sysconf(_SC_PAGESIZE);
	if (zone_size % page_size == 0)
		return(mmap(0, zone_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
	else
		return(mmap(0, ((zone_size / page_size) + 1) * page_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
	return(NULL);
}
