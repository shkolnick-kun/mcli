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
#ifndef MCLI_H
#define MCLI_H

#ifndef MCLI_OPT_DELIM
#define MCLI_OPT_DELIM " "
#endif/*MCLI_OPT_DELIM*/

#ifndef MCLI_STR_DELIM
#define MCLI_STR_DELIM "\""
#endif/*MCLI_STR_DELIM*/

/*Command main function pointer*/
typedef int (*mcli_fp)(int, char **);

typedef struct
{
    mcli_fp cmain;/*Command main func*/
    char *  name; /*Command name*/
    char *  desc; /*Command description*/
}
mcli_cmd_st;

typedef struct
{
    mcli_cmd_st * cmd;  /*A pointer to commands array*/
    char       ** argv; /*A pointer to argv buffer*/
    int           csz;  /*Commands array size*/
    int           alim; /*Argv array limit*/
}
mcli_shell_st;

typedef enum
{
    MCLI_ST_OK     =  0, /*OK*/
    MCLI_ST_EOOBA  = -1, /*Out of bands access*/
    MCLI_ST_ENOCMD = -2, /*Command not found*/
    MCLI_ST_EARG   = -3, /*Illegal argument*/
    MCLI_ST_EPARSE = -4,  /*Parsing error*/
    MCLI_ST_EILPTR = -5  /*Illegal function pointer*/
}
mcli_status_en;

int mcli_strlen(char * str, int lim);                       /*It's NOT compatible with standard strlen!*/
int mcli_strcmp(char * a, char * b, int lim);               /*It's NOT compatible with standard strcmp!*/
/*WARNING: dlen is tusted parameter, so don't mess it up!*/
int mcli_strtok(char ** pts,const char * d, int slim, int dlen); /*It's NOT compatible with standard strtok!*/
/*
NOTE: this is safer version of mcli_strtok!,
NOTE: d is c-string, containing delimiters!*/
#define MCLI_STRTOK(pts, d, slim) (mcli_strtok(pts, d, slim, sizeof(d) - 1))

#define MCLI_SHELL_DECL(shell, cmd, argv) \
mcli_shell_st shell = {cmd, argv, sizeof(cmd)/sizeof(mcli_cmd_st), sizeof(argv)/sizeof(char *)};

int mcli_shell_parse(mcli_shell_st * shell, char * buf, int lim);

#endif // MCLI_H
