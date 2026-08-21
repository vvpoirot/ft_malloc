#include "ft_malloc.h"

int main() {
	char *str = (char *)ft_malloc(240);
	char *str2 = (char *)ft_malloc(140);
	char *str3 = (char *)ft_malloc(1025);
	char *str4 = (char *)ft_malloc(55);

	if (!str)
	{
		printf("❌ Failled on str \n");
		return (1);
	}

	if (!str2)
	{
		printf("❌ Failled on str2 \n");
		return (1);
	}

	if (!str3)
	{
		printf("❌ Failled on str3 \n");
		return (1);
	}
	
	if (!str4)
	{
		printf("❌ Failled on str4 \n");
		return (1);
	}

	show_alloc_mem();
	str2 = ft_realloc(str2, 48);
	ft_printf("\n");

	show_alloc_mem();
	str2 = ft_realloc(str, 140);
	ft_printf("\n");

	show_alloc_mem();
	ft_printf("\n");
	
	ft_free(str);
	ft_free(str3);
	ft_free(str4);
	
	show_alloc_mem();
	ft_printf("\n");
	
	ft_free(str2);

	show_alloc_mem();

	return (0);
}
