#include <cstdio>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "myProcess.h"

static const char* prompt {"$$"};
static const char token = ' ';

static const size_t LOCALBUF_SIZE = 1 << 7;
static char localBuf[ LOCALBUF_SIZE ];

static const int MAX_OPTION_CNT = 1 << 7;
static const int MAX_COMMAND_LEN = 1 << 7;

static const char builtInCmd[][MAX_COMMAND_LEN] = {
  "cd",
  "echo",
};

/* Split command into arguments
 * 
 */
static int SplitCommand(char *cmd, char *argv[])
{
  int idx = 0;
  int argc = 0;
  int cmdLen = strlen(cmd);

  //while(idx++ < cmdLen)
  for(idx = 0; idx < cmdLen; idx++)
  {
    if(cmd[idx] == token) 
    {
      continue; 
    }
    argv[argc++] = cmd + idx; 
    while(idx < cmdLen && cmd[idx] != token)
    {
      idx++;
    }
    cmd[idx]='\0'; 
  }
  return argc;
}

/* Show shell prompt
 *
 */
int ShowPrompt()
{
  return printf("%s", prompt);
}

/* Get one input line to buffer
 *
 */
int GetOneLine(char* buf)
{
  int len {0};
  char c;
  do{
    c = getchar();
    buf[len] = c;
    if(c == EOF)
    {
      return len;
    }
  }while(c != '\n' && c != '\0'&& ++len);
  buf[len] = '\0';
  return len;
}

static void enterDirectory(char* dirStr){
  int result = chdir(dirStr);
  if(result == 0)
  {
    if(!getcwd(localBuf, LOCALBUF_SIZE))
    {
      printf("Currently working directory: %s", localBuf);
      return;
    }
  }
  printf("Execution error!");
}

static int BuiltInCommand(int argc, char** argv)
{
  int result = 1;
  if(!strcmp(argv[0], "cd"))
  {
    if(argc < 2)
    {
      printf("No directory argument");
      return result;
    }
    enterDirectory(argv[1]);
  }
  else
  {
    // Nothing executed
    result = 0;
  }
  return result;
}



// Execute a command
void ExecCommand(char *cmdWithOptions)
{
  char* options[MAX_OPTION_CNT];
  /* TODO 1. pipeline and redirection */

  /* 2. format current command */
  int optionCnt = SplitCommand(cmdWithOptions, options);
  printd("Split result:\n");
  for(int i=0; i<optionCnt; i++) printd("[%d] \"%s\"\n", i, options[i]);

  /* 3, execute command */
  ExecCommand
}
