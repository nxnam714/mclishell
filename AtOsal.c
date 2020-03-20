#include "AtOsal.h"
#include "ATCliAPI.h"


clish_shell_builtin_t ALLCLISHCMD_LIST[] = 
{
  DEF_SDKCOMMAND_CLISHBUILTIN("close shell", CmdCliClientExit),
  DEF_SDKCOMMAND_CLISHBUILTIN("device init", cliAppDeviceInit),
  DEF_SDKCOMMAND_CLISHBUILTIN("exit", CmdCliClientExit),
};


static int clish_shell_builtin_cmp(char *cmd, clish_shell_builtin_t *b)
{
	return strcmp(cmd, b->name);
}

static char *ATReadLine()
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
            fprintf(stderr, "AT: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }
  }
}
/**
   @brief Split a line into tokens (very naively).
   @param line The line.
   @return Null-terminated array of tokens.
 */
static char **ATSplitLine(char *line)
{
  int bufsize = AT_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char*));
  char *token, **tokens_backup;

  if (!tokens) 
  {
    fprintf(stderr, "AT: allocation error\n");
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
            fprintf(stderr, "AT: allocation error\n");
            exit(EXIT_FAILURE);
         }
      }

      token = strtok(NULL, AT_TOK_DELIM);
   }
   tokens[position] = NULL;

   return tokens;
}

static int ATExecute(char *args)
{

	clish_shell_builtin_t *item;
  item = (clish_shell_builtin_t*) bsearch (args, ALLCLISHCMD_LIST, 
		3, sizeof (struct clish_shell_builtin), (int(*)(const void*,const void*))clish_shell_builtin_cmp);
	if (item == NULL)
  {
    return CmdCliClientDefault();
  }
	return item->callback();
}


void ATCliStart(void)
{
  char *line = NULL;
  char **args = NULL;
  int status = 0;

  do
  {
    printf("AT > ");
      line = ATReadLine();
      //args = ATSplitLine(line);
      status = ATExecute(line);

      if (line)
        free(line);
      if (args)
        free(args);
    } while (status);

}