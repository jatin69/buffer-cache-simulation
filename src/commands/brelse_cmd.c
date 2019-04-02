#include "./../bufferCache.h"

/**Command Handler : brelse <blockNumber>
 * 
 * Runs the brelse algorithm for the specified block
*/
void brelse_cmd(int argc, char *argv[]) { 
  if (argc <= 1) {
    printf("Please specify the block number\n");
  } else {
    if (!isalpha(atoi(argv[1]))) {
      Buffer *p = searchBlockInHashQueue(atoi(argv[1]));
      if(p==NULL){
        printf("Specified Block not present in cache\n");
      }
      brelse(p);
    } else {
      printf("Block number should be a natural number present in cache\n");
    }
  }
}