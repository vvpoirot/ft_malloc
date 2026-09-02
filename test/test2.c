#include <stdlib.h>
#include "../libft/libft.h"
#include "../includes/ft_malloc.h"

int main() {
    ft_printf("==================================================\n");
    ft_printf("TEST 1: 120 alloc TINY (64 octets)\n");
    ft_printf("==================================================\n");

    char *ptrs_one[150];
    for (int i = 0; i < 150; i++) {
        ptrs_one[i] = (char *)malloc(64); // <= 128 -> TINY
        if (!ptrs_one[i]) {
            ft_printf("❌ Failed on ptrs_one[%d]\n", i);
            return (1);
        }
        ft_memset(ptrs_one[i], 'A' + (i % 26), 64);
    }

    show_alloc_mem();

    ft_printf("\n==================================================\n");
    ft_printf("TEST 2: 20 alloc SMALL (512 octets)\n");
    ft_printf("==================================================\n");

    char *ptrs_two[20];
    for (int i = 0; i < 20; i++) {
        ptrs_two[i] = (char *)malloc(512); // > 128 && <= 1024 -> SMALL
        if (!ptrs_two[i]) {
            ft_printf("❌ Failed on ptrs_two[%d]\n", i);
            return (1);
        }
        ft_memset(ptrs_two[i], 'B' + (i % 26), 512);
    }

    show_alloc_mem();

    ft_printf("\n==================================================\n");
    ft_printf("TEST 3: Free and Realloc (TINY to LARGE)\n");
    ft_printf("==================================================\n");

    for (int i = 0; i < 150; i += 2) {
        free(ptrs_one[i]);
        ptrs_one[i] = NULL;
    }

    show_alloc_mem();

    ptrs_one[1] = realloc(ptrs_one[1], 2048);
    show_alloc_mem();

    ft_printf("\n==================================================\n");
    ft_printf("TEST 4: Free every alloc\n");
    ft_printf("==================================================\n");

    for (int i = 1; i < 150; i += 2) {
        if (ptrs_one[i])
            free(ptrs_one[i]);
    }

    for (int i = 0; i < 20; i++) {
        free(ptrs_two[i]);
    }

    show_alloc_mem();

    ft_printf("\n✅ ALL TEST PASSED !\n");
}
