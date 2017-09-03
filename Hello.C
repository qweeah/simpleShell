#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "myProcess.h" //TODO

const int INPUT_BUF_SIZE = 1 << 12;

int main()
{
  char input_buf[INPUT_BUF_SIZE];
  while(ShowPrompt())
  {
    GetOneLine(input_buf);

    // enter: continue || exit || EOF
    if(!strlen(input_buf)) continue;
    if(input_buf[0] == EOF || !strcmp(input_buf, "exit")) break;

    /* Execute command */
    ExecInput(input_buf, -1);
  }
  return 0;
}
