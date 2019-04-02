#include "./../bufferCache.h"

void getblk_cmd(int argc, char *argv[]) {
  if (argc <= 1) {
    printf("Please specify block number\n");
  } else {
    int t = atoi(argv[1]);
    Buffer *allocatedBuffer = getblk(t);
  }
}