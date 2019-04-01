#include "./bufferCache.h"
#include "./externVariables.h"
#include "./commands/commands.h"

int bufferHasBeenInitialised = 0;

#define MAX_LINE_SIZE 1024

int parseUserInput(char *cmdline, char **argv);

int main() {
  
  char user_string[MAX_LINE_SIZE];
  
  while (1) {
    
	printf("➜ ");
	if(fgets(user_string, MAX_LINE_SIZE, stdin)==NULL){
    exit(1);
  };
	
  char *argv[16];
  int argc = parseUserInput(user_string, argv);
  if (argc == 0) { continue; }

	commandFunctionMap *p = commandTable;
    while(p->cmd) {
      if (strcmp(argv[0], p->cmd) == 0) {
        (*p->func)(argc, argv);
        break;
      }
	  p++;
    }

    if (p->cmd == NULL) {
      fprintf(stderr, "command not found: %s\n", argv[0]);
    }
  } // end: while

}
