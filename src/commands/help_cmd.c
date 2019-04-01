#include "./../bufferCache.h"
#include "./../externVariables.h"

void help_cmd(int num, char *name[]) {
  
  // init
  printf("init  \n");
  printf("\tinitialize hash list and free list and make the \n");
  printf("\tinitial state shown in the figure 2.15. \n\n");
  
  // Buffer
  printf("buf[n ...] \n");
  printf("\tIf there is no input value, ");
  printf("display all the status of the buffers.\n");
  printf("\tIf there is an input block number, ");
  printf("display the status of the buffer at the block number.\n\n");
  
  // hash
  printf("hash[n ...] \n");
  printf("\tIf there is no input value, ");
  printf("display all the hash list.\n");
  printf("\tIf there is an input hash key, ");
  printf("display the hash list at the hash key given from user.\n\n");
  
  // free
  printf("free\n");
  printf("\tDisplay free list\n\n");
  
  // getblk
  printf("getblk n\n");
  printf("\ttake the blockNumber from the user, execute getblk(n)\n\n");
  
  // brelse
  printf("brelse n\n");
  printf("\ttake the blockNumber from the user, execute brelse(bp), \n");
  printf("\twhere bp is the pointer to buffer header with blockNumber = n");
  printf("\n\n");
  
  // set
  printf("set n status [status]\n");
  printf("\tset the status of the buffer of blockNumber n to status\n\n");
  
  // reset
  printf("reset n status [status]\n");
  printf("\treset the status of the buffer of blockNumber n to status\n\n");
  
  // quit
  printf("exit the software\n\n");
}

