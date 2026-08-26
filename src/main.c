#include "ft_malloc.h"

int main() {
    printf("==================================================\n");
    printf("TEST 1: 120 alloc TINY (64 octets)\n");
    printf("==================================================\n");

    char *ptrs_one[150];
    for (int i = 0; i < 150; i++) {
        ptrs_one[i] = (char *)ft_malloc(64); // <= 128 -> TINY
        if (!ptrs_one[i]) {
            printf("❌ Failed on ptrs_one[%d]\n", i);
            return (1);
        }
        memset(ptrs_one[i], 'A' + (i % 26), 64);
    }

    show_alloc_mem();

    printf("\n==================================================\n");
    printf("TEST 2: 20 alloc SMALL (512 octets)\n");
    printf("==================================================\n");

    char *ptrs_two[20];
    for (int i = 0; i < 20; i++) {
        ptrs_two[i] = (char *)ft_malloc(512); // > 128 && <= 1024 -> SMALL
        if (!ptrs_two[i]) {
            printf("❌ Failed on ptrs_two[%d]\n", i);
            return (1);
        }
        memset(ptrs_two[i], 'B' + (i % 26), 512);
    }

    show_alloc_mem();

    printf("\n==================================================\n");
    printf("TEST 3: Free and Realloc (TINY to LARGE)\n");
    printf("==================================================\n");

    for (int i = 0; i < 150; i += 2) {
        ft_free(ptrs_one[i]);
        ptrs_one[i] = NULL;
    }

    show_alloc_mem();

    // ptrs_one[1] = ft_realloc(ptrs_one[1], 2048);
    show_alloc_mem();

    printf("\n==================================================\n");
    printf("TEST 4: Free every alloc\n");
    printf("==================================================\n");

    for (int i = 1; i < 150; i += 2) {
        if (ptrs_one[i])
            ft_free(ptrs_one[i]);
    }

    for (int i = 0; i < 20; i++) {
        ft_free(ptrs_two[i]);
    }

    show_alloc_mem();

    printf("\n✅ ALL TEST PASSED !\n");
}