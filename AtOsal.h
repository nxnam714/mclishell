#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AT_TOK_BUFSIZE 64
#define AT_TOK_DELIM " \t\r\n\a"
#define AT_RL_BUFSIZE 1024

#define DEF_SDKCOMMAND_CLISHBUILTIN(_cmdname, funcname) \
    { \
		.name = (char *)(size_t)_cmdname, \
		.callback = (clish_shell_builtin_fn_t*)funcname \
    }

typedef int clish_shell_builtin_fn_t(void);

typedef struct clish_shell_builtin{
    char *name;       
    clish_shell_builtin_fn_t *callback;
} clish_shell_builtin_t;


int cliAppDeviceInit();
int CmdCliClientExit();
//int CmdCliClientDefault();
void ATCliStart(void);

//extern clish_shell_builtin_t ALLCLISHCMD_LIST[];

