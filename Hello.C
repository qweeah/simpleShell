#include <iostream>
#include <cstdio>
#include <cstring>

#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
#include <wait.h>

#include "myProcess.h" //TODO

const int INPUT_BUF_SIZE = 1 << 12;

int main()
{
  char input_buf[INPUT_BUF_SIZE];
  int pid;
  int status;
  ShowPrompt(); //TODO : uncomment
  //while(ShowPrompt())
  {
    GetOneLine(input_buf);

    // enter: continue || exit||EOF end
    if(!strlen(input_buf)) return 0; //continue;
    if(input_buf[0] == EOF || !strcmp(input_buf, "exit")) return 0; //break;

    /* Execute command */
    ExecCommand(input_buf);
/*
    //fork
    pid = fork();
    if(pid == 0)
    {
      printf("Child\n");
      // exec
      printf("%s\n", input_buf);
      break;
    }
    else {
      pid = wait(&status);
      printf("Parent\n");
    }
*/
  }
  return 0;
}
