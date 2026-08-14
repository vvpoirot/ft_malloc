#include "ft_malloc.h"

int main() {
	char *str = (char *)ft_malloc(240);
	char *str2 = (char *)ft_malloc(140);

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

	printf("✅ Succès : %s (Adresse : %p)\n", str, (void *)str);
	printf("✅ Succès : %s (Adresse : %p)\n", str2, (void *)str2);

	return (0);
}
