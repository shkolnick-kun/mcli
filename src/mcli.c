/*
MIT License

Copyright (c) 2018 shkolnick-kun

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "mcli.h"

int mcli_strlen(char * str, int lim)
{
    int i;
    if (!str)
    {
        return MCLI_ST_EARG;
    }

    for (i = 0; i < lim; i++)
    {
        if (0 == str[i])
        {
            break;
        }
    }

    if (0 == lim - i)
    {
        /*Error*/
        return MCLI_ST_EOOBA;
    }
    return i;
}

int mcli_strcmp(char * a, char * b, int lim)
{
    int ret = 0;

    if (!a || !b)
    {
        return MCLI_ST_EARG;
    }

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

    if (!pts)
    {
        return MCLI_ST_EARG;
    }

    if (!*pts)
    {
        return MCLI_ST_EARG;
    }

    if (0 == slim)
    {
        /*Error*/
        return MCLI_ST_EOOBA;
    }
    /*Skip delimiters*/
    for(s = *pts; _mcli_is_in(*s, d, dlen); s++)
    {
        if (0 == --slim)
        {
            /*Error*/
            return MCLI_ST_EOOBA;
        }
    }
    /*This is token starting position! Which is "returned" to caller*/
    *pts = s;
    /*Count chars in the token!*/
    for (n = 0; _mcli_is_in(*s, d, dlen) == 0; s++, n++)
    {
        if (0 == *s)
        {
            /*EOL detected*/
            break;
        }
        if (0 == --slim)
        {
            /*Error*/
            return MCLI_ST_EOOBA;
        }
    }
    /*Skip delimiter.*/
    return n;/*return number of chars in the token*/
}

int mcli_shell_parse(mcli_shell_st * shell, char * buf, int lim)
{
    char * t_start;

    int len;
    int argc;
    int cmd_len;
    int i;
    char is_str;
    /*Check args*/
    if (!shell)
    {
        return MCLI_ST_EARG;
    }

    len = mcli_strlen(buf, lim);
    if (len <= 0)
    {
        return MCLI_ST_EOOBA;
    }
    /*Tokenize the command line*/
    len++;
    t_start = buf;
    argc    = 0;
    cmd_len = 0;
    is_str  = 0;
    while (t_start - buf < len)
    {
        i = MCLI_STRTOK(&t_start, MCLI_OPT_DELIM, len - (t_start - buf));

        if (i < 0)
        {
            /*Error*/
            return i;
        }

        if (i > 0)
        {
            int j;
            /*Found something!*/
            if (0 == cmd_len)
            {
                /*argv[0] is command name*/
                cmd_len = i;
            }
            /*Is it a new option?*/
            if (!is_str)
            {
                shell->argv[argc++] = t_start;
            }
            /*Try to find string delimiters*/
            for (j = 0; j < i; j++)
            {

                if (_mcli_is_in(t_start[j], MCLI_STR_DELIM, sizeof(MCLI_STR_DELIM) - 1))
                {
                    is_str ^= 1; /*Toggle the string flag*/
                }
            }
            /*Terminate the option only when all strings are closed*/
            if (!is_str)
            {
                t_start[i] = 0;
            }
        }

        t_start += i + 1;/*Skip delimiter*/
    }
    /*Check for unclosed strings!*/
    if (is_str)
    {
        return MCLI_ST_EPARSE;
    }
    /*Lookup the command.*/
    for (i = 0; i < shell->csz; i++)
    {
        mcli_cmd_st * cmd;

        cmd = shell->cmd + i;
        if (0 == mcli_strcmp(cmd->name, shell->argv[0], cmd_len))
        {
            /*Found the command now try to execute it*/
            if (cmd->cmain)
            {
                return cmd->cmain(argc, shell->argv);
            }
            else
            {
                return MCLI_ST_EILPTR;
            }
        }
    }
    return MCLI_ST_ENOCMD;
}
