#include "mcli.h"

int mcli_strlen(char * str, int lim)
{
    int i;
    for (i = 0; i < lim; i++)
    {
        if (0 == str[i])
        {
            break;
        }
    }

    if (0 == lim - i)
    {
        return MCLI_ST_EOOBA;
    }
    return i;
}

int mcli_strcmp(char * a, char * b, int lim)
{
    int ret = 0;
    while (lim--)
    {
        if (*a++ != *b++)
        {
            ret = 1;
            break;
        }
        if (0 == *a)
        {
            break;
        }
    }

    if (0 > lim)
    {
        return MCLI_ST_EOOBA;
    }


    if (0 != *b)
    {
        ret = 1;
    }

    return ret;
}
static inline int _mcli_is_in(char c, const char * d, int dlen)
{
    while (dlen--)
    {
        if (0 == *d++ - c)
        {
            return 1;
        }
    }
    return 0;
}

int mcli_strtok(char ** pts, const char * d, int slim, int dlen)
{
    char *s;
    int   n;
    /*Starting position*/
    s = *pts;
    /*Skip delimiters*/
    while (_mcli_is_in(*s, d, dlen))
    {
        s++;
        if (0 == --slim)
        {
            return MCLI_ST_EOOBA;
        }
    }
    /*This is token starting position! Which is "returned" to caller*/
    *pts = s;
    /*Count chars in the token!*/
    n    = 0;
    while (!_mcli_is_in(*s, d, dlen))
    {
        n++;
        s++;
        if (0 == --slim)
        {
            return MCLI_ST_EOOBA;
        }
    }

    return n;/*return number of chars in the token*/
}

