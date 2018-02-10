#ifndef MCLI_H
#define MCLI_H

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
    MCLI_ST_OK,      /*OK*/
    MCLI_ST_EOOB,    /*Out of bands access*/
    MCLI_ST_NOCMD,   /*Command not found*/
    MCLI_ST_EPARSE   /*Parsing error*/
}
mcli_status_en;

int mcli_strlen(char * str, int lim);
int mcli_strtok(char * str, int lim);
int mcli_strcmp(char * a, char * b, int lim);

#define MCLI_SHELL_DECL(shell, cmd, argv) \
mcli_shell_st shell = {cmd, argv, sizeof(cmd)/sizeof(mcli_cmd_st), sizeof(argv)/sizeof(char *)};

int mcli_shell_parse(mcli_shell_st shell, char * buf, int lim);

#endif // MCLI_H
