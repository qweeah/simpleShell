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
  //ShowPrompt(); //TODO : uncomment
  while(ShowPrompt())
  {
    GetOneLine(input_buf);

    // enter: continue || exit||EOF end
    if(!strlen(input_buf)) return 0; //continue;
    if(input_buf[0] == EOF || !strcmp(input_buf, "exit")) return 0; //break;

    /* Execute command */
    ExecInput(input_buf);
  }
  return 0;
}
