#include "./bufferCache.h"
#include "./commands/commands.h"

#define MAX_LINE_SIZE 1024

void init();
int parseUserInput(char *cmdline, char **argv);

int main() {

  char user_string[MAX_LINE_SIZE];

  // initialise data structures
  init();

  while (1) {

	// prompt for user
    printf("➜ ");
    if (fgets(user_string, MAX_LINE_SIZE, stdin) == NULL) {
      exit(1);
    };

	// parse user input properly
    char *argv[MAX_LINE_SIZE];
    int argc = parseUserInput(user_string, argv);
    if (argc == 0) {
      continue;
    }

	// match user entered command to appropriate command handler
    commandFunctionMap *p = commandTable;
    while (p->cmd) {
      if (strcmp(argv[0], p->cmd) == 0) {
        (*p->func)(argc, argv);
        break;
      }
      p++;
    }

	// if not match occurs, command is not available yet
    if (p->cmd == NULL) {
      fprintf(stderr, "command not found: %s\n", argv[0]);
    }
	
  } // end: while
}
