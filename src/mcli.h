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
    MCLI_ST_OK     =  0, /*OK*/
    MCLI_ST_EOOBA   = -1, /*Out of bands access*/
    MCLI_ST_ENOCMD  = -2, /*Command not found*/
    MCLI_ST_EPARSE = -15 /*Parsing error*/
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

int mcli_shell_parse(mcli_shell_st shell, char * buf, int lim);

#endif // MCLI_H
