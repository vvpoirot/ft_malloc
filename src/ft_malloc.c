#include "ft_malloc.h"

void* ft_malloc(size_t size) {
	size_t alignee_size = ALIGN(size);
	if (alignee_size <= TINY)
		ft_printf("%s // %d\n", "TINY", alignee_size);
	else if (alignee_size <= SMALL)
		ft_printf("%s // %d\n", "SMALL", alignee_size);
	else
		ft_printf("%s // %d\n", "LARGE", alignee_size);
	return (NULL);
}
