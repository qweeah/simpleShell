#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include<sys/types.h>
#include<wait.h>

#include "myProcess.h"

static const char* prompt {"$$"};
static const char token = ' ';

static const size_t LOCALBUF_SIZE = 1 << 7;

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

/* CD - enter the given directory
 *
 */
static void enterDirectory(char* dirStr){
  int result = chdir(dirStr);
	char *pwdStr = (char *)malloc(sizeof(char) * LOCALBUF_SIZE);
  if(result == 0)
  {
    if(getcwd(pwdStr, LOCALBUF_SIZE) != NULL)
    {
      printf("Currently working directory: %s\n", pwdStr);
			free(pwdStr);
      return;
    }
  }
  printf("Bish: cd: %s; error no such path or directory!\n", dirStr);
}

/* Builtin Commands in shell
 *
 */
static int BuiltInCommand(int argc, char** argv)
{
  int result = 1;
  if(!strcmp(argv[0], "cd"))
  {
    if(argc < 2)
    {
			// Default enter $HOME
			enterDirectory(getenv("HOME"));
      return result;
    }
    enterDirectory(argv[1]);
  }
	else if(!strcmp(argv[0], "echo"))
  {
		if(argc < 2)
    {
			// Default echo nothing
      printf("\n");
      return result;
    }
		printf("%s\n", argv[1]);
	}
  else
  {
    // Nothing executed
    result = 0;
  }
  return result;
}

// Divide pipe
char* FindPipe(char *rawInputLine)
{
	char* nextCommand = nullptr;
	while(*rawInputLine != '\0')
	{
		if(*rawInputLine == '|')
		{
			*rawInputLine = '\0';
			nextCommand = rawInputLine + 1;
			break;
		}
		rawInputLine++;
	}
	return nextCommand;
}

static void ExecCommand(int argc, char** argv, int fdIn, int fdOut)
{
	//fork
	int status;
	pid_t pid = fork();
	if(pid == 0)
	{
		// pipe
		if(fdOut > 0) dup2(fdOut, STDOUT_FILENO);
		if(fdIn > 0) dup2(fdIn, STDIN_FILENO);
		// exec
		if(execvp(*argv, argv) < 0)
		{
			perror("Unable to execute command");
			exit(EXIT_FAILURE);
		}
		exit(0);
	}
	else
	{
		while(wait(&status) != pid);
		close(fdOut); // write done
	}
}

// Execute a command
void ExecInput(char *rawInputLine, int fdIn)
{
  char* options[MAX_OPTION_CNT];
	char* nextCommand;
  int isBuiltIn {0};
	int pipeFd[2] = {-1, -1};

  /* 1. pipeline and TODO redirection */
	nextCommand = FindPipe(rawInputLine);
	if(nextCommand != nullptr) {
		pipe(pipeFd);
	}

  /* 2. format current command */
  int optionCnt = SplitCommand(rawInputLine, options);
  printd("Split result:\n");
  for(int i=0; i<optionCnt; i++) printd("[%d] \"%s\"\n", i, options[i]);

  /* 3. execute builtin command */
	isBuiltIn = BuiltInCommand(optionCnt, options);

	/* 4. exec external */
	if(!isBuiltIn)
	{
		ExecCommand(optionCnt, options, fdIn, pipeFd[1]);
	}

	if(nextCommand != nullptr) {
		ExecInput(nextCommand, pipeFd[0]);
	}
}
