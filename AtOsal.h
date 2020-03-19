#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEF_SDKCOMMAND_CLISHBUILTIN(_cmdname, funcname) \
    { \
		.name = (char *)(size_t)_cmdname, \
		.callback = (clish_shell_builtin_fn_t*)funcname \
    }

typedef void clish_shell_builtin_fn_t (void);

typedef struct clish_shell_builtin{
    char *name;       
    clish_shell_builtin_fn_t *callback;
} clish_shell_builtin_t;


void cliAppDeviceInit();
void CmdCliClientExit();
void ATCliStart(void);

//extern clish_shell_builtin_t ALLCLISHCMD_LIST[];

