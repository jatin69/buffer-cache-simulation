#include "./../bufferCache.h"
#include "./../externVariables.h"

void help_cmd(int num, char *name[]) {
  
  printf("\n\n");
  // init
  printf("init  \n");
  printf("\tinitialize hash list and free list and make the \n");
  printf("\tinitial state shown in the figure 2.15. \n\n");
  
  // Buffer
  printf("buf \n");
  printf("\tdisplay the status of all the buffers.\n");
  
  // hash
  printf("hash\n");
  printf("\tIf there is no input value, display all the hash list.\n");
  
  // free
  printf("free\n");
  printf("\tDisplay free list\n\n");
  
  // waitingQueue
  printf("wait\n");
  printf("\tDisplay waiting Queue\n\n");

  // getblk
  printf("getblk n\n");
  printf("\ttake the blockNumber from the user, execute getblk(n)\n\n");
  
  // brelse
  printf("brelse n\n");
  printf("\ttake the blockNumber from the user, execute brelse() \n\n");
  
  // set
  printf("set <blockNumber> <statusCode> \n");
  printf("\tset the status of the buffer of blockNumber n to status\n\n");
  
  // reset
  printf("reset <blockNumber> <statusCode> \n");
  printf("\treset the status of the buffer of blockNumber n to status\n\n");
  
  // quit
  printf("exit\n");
  printf("\tTo quit the simulation\n\n");
}

