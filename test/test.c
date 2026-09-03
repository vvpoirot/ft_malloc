#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *p = malloc(10);

    free(p);
    free(p);

    printf("%p\n", (void *)p);

    return 0;
}