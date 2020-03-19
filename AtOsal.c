#include "AtOsal.h"


void cliAppDeviceInit()
{
	printf("cliAppDeviceInit\n");
}
void CmdCliClientExit()
{
	printf("CmdCliClientExit\n");
}
int clish_shell_builtin_cmp(char *cmd, clish_shell_builtin_t *b)
{
	//printf("%s %s %d\n", cmd, b->name, strcmp(cmd, b->name));
	return strcmp(cmd, b->name);
}
clish_shell_builtin_t ALLCLISHCMD_LIST[] = 
{
	DEF_SDKCOMMAND_CLISHBUILTIN("close shell", CmdCliClientExit),
	DEF_SDKCOMMAND_CLISHBUILTIN("device init", cliAppDeviceInit),
};
#define AT_RL_BUFSIZE 1024

char *ATReadLine()
{
   int bufsize = AT_RL_BUFSIZE;
   int position = 0;
   char *buffer = malloc(sizeof(char) * bufsize);
   int c;

   if (!buffer) 
   {
      fprintf(stderr, "NA: allocation error\n");
      exit(EXIT_FAILURE);
   }
   while (1) {
      // Read a character
      c = getchar();

      if (c == EOF) 
      {
         exit(EXIT_SUCCESS);
      } 
      else if (c == '\n') 
      {
         buffer[position] = '\0';
         return buffer;
      } 
      else 
      {
         buffer[position] = c;
      }
      position++;

      // If we have exceeded the buffer, reallocate.
      if (position >= bufsize) 
      {
         bufsize += AT_RL_BUFSIZE;
         buffer = realloc(buffer, bufsize);
         if (!buffer) {
            fprintf(stderr, "NA: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }
  }
}

#define AT_TOK_BUFSIZE 64
#define AT_TOK_DELIM " \t\r\n\a"
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
char **ATSplitLine(char *line)
{
  int bufsize = AT_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) 
  {
    fprintf(stderr, "NA: allocation error\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, AT_TOK_DELIM);
  while (token != NULL) 
  {
      tokens[position] = token;
      position++;

      if (position >= bufsize) 
      {
         bufsize += AT_TOK_BUFSIZE;
         tokens_backup = tokens;
         tokens = realloc(tokens, bufsize * sizeof(char*));
         if (!tokens) 
         {
            free(tokens_backup);
            fprintf(stderr, "NA: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }

      token = strtok(NULL, AT_TOK_DELIM);
   }
   tokens[position] = NULL;

   return tokens;
}

int ATExecute(char *args)
{

	clish_shell_builtin_t *item = (clish_shell_builtin_t*) bsearch (args, ALLCLISHCMD_LIST, 
		2, sizeof (struct clish_shell_builtin), (int(*)(const void*,const void*))clish_shell_builtin_cmp);
	item->callback();
	//printf("%s\n", args);
	return 1;
}


void ATCliStart(void)
{
    char *line = NULL;
    char **args = NULL;
    int status;

    do
    {
        printf("> ");
        line = ATReadLine();
        //printf("%s\n", line);
        //args = ATSplitLine(line);
        status = ATExecute(line);


        if (line)
        	free(line);
        if (args)
        	free(args);
    } while (status);
}