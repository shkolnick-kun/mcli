#include <stdio.h>
#include <stdlib.h>

#include <mcli.h>

char a[] = "mars";
char b[] = "marsian";
char c[] = "earth";
char d[] = "\0";
char e[] = "ololo";

const char d0[] = "";
const char d1[] = " ,_,\"";

char f[] = "   Mars is_not_a \"star\"";

void test_strtok(const char d)
{

}

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
    char * s;
    s = f;
    while (s - f < sizeof(f))
    {
        int i;
        i = MCLI_STRTOK(&s, d0, sizeof(f) - (s - f));
        if (i < 0)
        {
            printf("Error!");
            break;
        }
        s[i] = 0;
        if (i)
        {
            printf("The token is: %s, %d\n", s, i);
        }
        s += i + 1;
    }

    s = f;
    while (s - f < sizeof(f))
    {
        int i;
        i = MCLI_STRTOK(&s, d1, sizeof(f) - (s - f));
        if (i < 0)
        {
            printf("Error!");
            break;
        }
        s[i] = 0;
        if (i)
        {
            printf("The token is: %s, %d\n", s, i);
        }
        s += i + 1;
    }

    s = d;
    printf("STRTOK(%s, d1, 0) = %d\n", d, MCLI_STRTOK(&s, d1, sizeof(d)));

    s = e;
    printf("STRTOK(%s, d1, 0) = %d\n", e, MCLI_STRTOK(&s, d1, 0));

    s = e;
    printf("STRTOK(%s, d1, *) = %d\n", e, MCLI_STRTOK(&s, d1, sizeof(e)));

    s = f;
    printf("STRTOK(%s, d1, 1) = %d\n", f, MCLI_STRTOK(&s, d1, 2));

    s = f;
    printf("STRTOK(%s, d1, 4) = %d\n", f, MCLI_STRTOK(&s, d1, 4));

    printf("The End!");
    return 0;
}
