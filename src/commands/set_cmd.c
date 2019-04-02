#include "./../bufferCache.h"

int parseStatus(char *argv);

void set_cmd(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("Specify block number and status code\n");
  } 
  else {

    int blockNumber = atoi(argv[1]);
    Buffer *buffer = searchBlockInHashQueue(blockNumber);
    
    if (buffer == NULL) {
      printf("invaid cannot get buffer\n");
      return;
    }
    for (int i = 2; i < argc; i++) {
      addState(buffer, parseStatus(argv[i]));
    }
  }
}
