#include "./../bufferCache.h"

int parseStatus(char *argv);

/**Command Handler : set <blockNumber> <statusCode> 
 * 
 * Adds the specified statusCode in the specified block.
*/

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
      STATE state = parseStatus(argv[i]);
      addState(buffer, state);
      if(state == BUFFER_BUSY){
        removeBufferFromFreeList(buffer);
      }
    }
  }
}
