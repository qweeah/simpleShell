#define printd //printf

/* Show shell prompt */
int ShowPrompt();

/* Read a whole line of command */
int GetOneLine(char*);

/* Built-in command */
void ExecInput(char *rawInputLine, int dfIn);
