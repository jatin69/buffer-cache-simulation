#include "./../bufferCache.h"
#include "./../externVariables.h"

Buffer *Clone(int blockNumber);

void brelse_cmd(int argc, char *argv[]) {
  if (!initnum) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 1) {
    printf("Please specify the block number\n");
  } else {
    if (!isalpha(atoi(argv[1]))) {
      Buffer *p = Clone(atoi(argv[1]));
      brelse(p);
    } else {
      printf("Block number should be a natural number\n");
    }
  }
}