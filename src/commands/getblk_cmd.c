#include "./../bufferCache.h"

/**Command Handler : getblk <blockNumber>
 * 
 * Runs the getblk algorithm for the specified block
*/
void getblk_cmd(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Please specify block number\n");
  } else {
    int t = atoi(argv[1]);
    Buffer *allocatedBuffer = getblk(t);
    if(allocatedBuffer != NULL){
    	printf("Buffer Allocated Successfully.\n");
    }
  }
}