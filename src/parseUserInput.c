#include "./bufferCache.h"

/**Parse User Input 
 * 
*/
int parseUserInput(char *cmdline, char **argv) {
  
  char *buffer = calloc(100, sizeof(char));
  strcpy(buffer, cmdline);
  
  // replace null terminator to space
  buffer[strlen(buffer) - 1] = ' ';     
  while (*buffer && (*buffer == ' ')) {
    buffer++;
  }

  char* delim = strchr(buffer, ' ');
  int argc = 0;

  while (delim) {
    *delim = '\0';
    argv[argc++] = buffer;
    buffer = delim + 1;
    while (*buffer && (*buffer == ' ')) {
      buffer++;
    }
    delim = strchr(buffer, ' ');
  }
  argv[argc] = NULL;
  if (argc == 0) {
    printf("No argument is obtained\n");
    return 0;
  } else {
    for (int i = 0; i < argc; i++) {
      puts(argv[i]);
    }
  }
  return argc;
}
