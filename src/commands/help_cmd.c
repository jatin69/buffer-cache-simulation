#include "./../bufferCache.h"

/**Command Handler : help
 * 
 * Displays information about all possible commands
*/
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
  printf("\tDisplay free list\n");
  
  // waitingQueue
  printf("wait\n");
  printf("\tDisplay waiting Queue\n");

  // quit
  printf("exit\n");
  printf("\tTo exit the simulation\n\n");

  // getblk
  printf("getblk <blockNumber>\n");
  printf("\n\tTake the blockNumber from the user, execute getblk(n)\n\n");
  
  // brelse
  printf("brelse <blockNumber>\n");
  printf("\n\tTake the blockNumber from the user, execute brelse() \n\n");
  
  // set
  printf("set <blockNumber> <statusCode> \n");
  printf("\n\tSet the status of the buffer to status code\n\n");
  printf("\tB : Buffer Busy\n");
  printf("\tV : Buffer Data is Valid\n");
  printf("\tD : Buffer is marked delayed write\n");
  printf("\tK : Kernet is reading/writing buffer to disk\n");
  printf("\tW : Buffer is awaited by some other process\n");
  printf("\tO : Buffer Data is OLD\n\n");
  
  // reset
  printf("reset <blockNumber> <statusCode> \n");
  printf("\n\tReset the status of the buffer to status code\n\n");
  printf("\tB : Buffer Busy\n");
  printf("\tV : Buffer Data is Valid\n");
  printf("\tD : Buffer is marked delayed write\n");
  printf("\tK : Kernet is reading/writing buffer to disk\n");
  printf("\tW : Buffer is awaited by some other process\n");
  printf("\tO : Buffer Data is OLD\n\n");
}

