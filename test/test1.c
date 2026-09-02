#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    char *str;

    str = malloc(65536);
    if (!str)
        return (1);

    str[0] = 'H';
    str[1] = 'e';
    str[2] = 'l';
    str[3] = 'l';
    str[4] = 'o';
    str[5] = '\0';

    printf("%s\n", str);

    free(str);

    return (0);
}
