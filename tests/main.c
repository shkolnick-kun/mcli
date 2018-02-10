#include <stdio.h>
#include <stdlib.h>

#include <mcli.h>

char a[] = "mars";
char b[] = "marsian";
char c[] = "earth";
char d[] = "\0";
char e[] = "ololo";

int main()
{
    /*stren*/
    printf("Len(%s) = %d error\n", a, mcli_strlen(a, 0));
    printf("Len(%s) = %d error\n", a, mcli_strlen(a, 1));
    printf("Len(%s) = %d\n", a, mcli_strlen(a, sizeof(a)));
    printf("Len(%s) = %d\n", d, mcli_strlen(d, sizeof(d)));

    /*strcmp*/
    printf("CMP(%s, %s) = %d error\n", a, a, mcli_strcmp(a, a, 0));
    printf("CMP(%s, %s) = %d error\n", a, a, mcli_strcmp(a, a, 1));
    printf("CMP(%s, %s) = %d\n", a, a, mcli_strcmp(a, a, sizeof(a)));
    printf("CMP(%s, %s) = %d\n", a, b, mcli_strcmp(a, b, sizeof(a)));
    printf("CMP(%s, %s) = %d\n", a, c, mcli_strcmp(a, c, sizeof(a)));
    printf("CMP(%s, %s) = %d\n", e, c, mcli_strcmp(a, e, sizeof(e)));

    /*strtok*/

    printf("Hello world!\n");
    return 0;
}
