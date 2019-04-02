#include "./../bufferCache.h"

int parseStatus(char *argv);

/**Command Handler : reset <blockNumber> <statusCode> 
 * 
 * Remove the specified statusCode from the specified block.
*/
void reset_cmd(int argc, char *argv[]) {
  if (argc <= 2) {
    printf("Specify block number and status code\n");
  } 
  else {
    int blockNumber = atoi(argv[1]);
    Buffer *buffer = searchBlockInHashQueue(blockNumber);
    
    if (buffer == NULL) {
      printf("Invaid. This Block is not in cache currently.\n");
      return;
    }
    for (int i = 2; i < argc; i++) {
      STATE state = parseStatus(argv[i]);
      removeState(buffer, state);
      if(state == BUFFER_BUSY){
        freeList_push_back(freeListDummyHead, buffer);
      }
    }
  }
}