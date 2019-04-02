#include "./../bufferCache.h"

void brelse_cmd(int argc, char *argv[]) { 
  if (argc <= 1) {
    printf("Please specify the block number\n");
  } else {
    if (!isalpha(atoi(argv[1]))) {
      Buffer *p = searchBlockInHashQueue(atoi(argv[1]));
      brelse(p);
    } else {
      printf("Block number should be a natural number\n");
    }
  }
}