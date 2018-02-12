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

char tst_cmd_str1[] = "rm -rf /";
char tst_cmd_str2[] = "cmd0 a b c";
char tst_cmd_str3[] = "cmd1 ololo ololo";
char tst_cmd_str4[] = "cmd0 a \"b c\" d \"e f\" gg";
char tst_cmd_str5[] = "cmd0 a \"b\"\"c\" d \"e f\" gg";
char tst_cmd_str6[] = "cmd0 a b \"c";
char tst_cmd_str7[] = "cmd1";

int tst_cmd_main(int argc, char ** argv)
{
    while (argc--)
    {
        printf("%s\n", *argv++);
    }

    return 0;
}

mcli_cmd_st tst_cmd[] =
{
    {
        .name = "cmd0",
        .desc = "Test command 0",
        .cmain = tst_cmd_main
    },
    {
        .name = "cmd1",
        .desc = "Test command 1",
        .cmain = tst_cmd_main
    }
};

char * abuf[] = {0,0,0,0,0,0,0,0,0,0};

MCLI_SHELL_DECL(tst_shell, tst_cmd, abuf);

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
        printf("Delimiter is: \"%c\"\n", s[i]);
        s[i] = 0;
        if (i)
        {
            printf("The token is: %s, %d\n", s, i);
        }
        s += i + 1;
    }

    s = d;
    printf("STRTOK(%s, d1, 0) = %d\n", d, MCLI_STRTOK(&s, d1, sizeof(d)));

    s = d1;
    printf("STRTOK(%s, d1, 4) = %d\n", d1, MCLI_STRTOK(&s, d1, sizeof(d1)));

    s = e;
    printf("STRTOK(%s, d1, 0) = %d\n", e, MCLI_STRTOK(&s, d1, 0));

    s = e;
    printf("STRTOK(%s, d1, *) = %d\n", e, MCLI_STRTOK(&s, d1, sizeof(e)));

    s = f;
    printf("STRTOK(%s, d1, 2) = %d\n", f, MCLI_STRTOK(&s, d1, 2));

    s = f;
    printf("STRTOK(%s, d1, 4) = %d\n", f, MCLI_STRTOK(&s, d1, 4));


    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, c, sizeof(c)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, d, 1));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, d, 0));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str1, 0));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str1, sizeof(tst_cmd_str1)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str2, sizeof(tst_cmd_str2)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str3, sizeof(tst_cmd_str3)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str4, sizeof(tst_cmd_str4)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str5, sizeof(tst_cmd_str5)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str6, sizeof(tst_cmd_str6)));
    printf("\nResult is: %d\n", mcli_shell_parse(&tst_shell, tst_cmd_str7, sizeof(tst_cmd_str7)));


    printf("The End!\n");
    return 0;
}
