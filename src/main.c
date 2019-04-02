#include "./bufferCache.h"
#include "./commands/commands.h"

#define MAX_LINE_SIZE 1024

void init();
int parseUserInput(char *cmdline, char **argv);

int main() {
  
  char user_string[MAX_LINE_SIZE];
  // initialise buffer cache to figure 3.2
  init();
    
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
