#include "./../bufferCache.h"

void help_cmd(int num, char *name[]) {
  
  printf("\n\n");
  
  // Buffer
  printf("buf \n");
  printf("\tDisplay the status of all the buffers.\n");
  
  // hash
  printf("hash\n");
  printf("\tDisplay all the Hash Queues.\n");
  
  // free
  printf("free\n");
  printf("\tDisplay free list\n\n");
  
  // waitingQueue
  printf("wait\n");
  printf("\tDisplay waiting Queue\n\n");

  // getblk
  printf("getblk n\n");
  printf("\tTake the blockNumber from the user, execute getblk(n)\n\n");
  
  // brelse
  printf("brelse n\n");
  printf("\tTake the blockNumber from the user, execute brelse() \n\n");
  
  // set
  printf("set <blockNumber> <statusCode> \n");
  printf("\tSet the status of the buffer of blockNumber n to status\n\n");
  
  // reset
  printf("reset <blockNumber> <statusCode> \n");
  printf("\tReset the status of the buffer of blockNumber n to status\n\n");
  
  // quit
  printf("exit\n");
  printf("\tTo quit the simulation\n\n");
}

