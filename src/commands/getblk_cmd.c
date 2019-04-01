#include "./../bufferCache.h"
#include "./../externVariables.h"


void getblk_cmd(int argc, char *argv[]) {
  if (!bufferHasBeenInitialised) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 1) {
    printf("Please specify block number\n");
  } else {
    int t = atoi(argv[1]);
    
    Buffer *allocatedBuffer = getblk(t);
    
  }
}