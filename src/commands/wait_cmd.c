#include "./../bufferCache.h"

/**Command Handler : wait
 * 
 * Displays the process waiting Queue.
 *
 * Waiting Queue contains the process which are currently sleeping
 * and waiting for some buffer to get free.
*/
void wait_cmd(int argc, char *argv[]){
  printWaitingQueue();
}