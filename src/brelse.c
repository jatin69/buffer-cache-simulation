#include "./bufferCache.h"

/**Brelse (Block Release) algorithm
 * 
*/
void brelse(Buffer *buffer) {
  if(buffer == NULL){
    return;
  }

  // wakeupProcesses(WAITING_FOR_ANY_BUFFER);
  printf("Wakeup processes wating for any buffer\n");
  
  if (isInState(buffer, BUFFER_BUSY | BUFFER_DATA_VALID | BUFFER_AWAITED)) {
    // wakeupProcesses(WAITING_FOR_THIS_BUFFER);
    printf("Wakeup processes waiting for buffer of blockNumber %d\n", buffer->blockNumber);
  }

  // raise_cpu_level();
  printf("Raising CPU level to block interrupts.\n");
  
  // choose whether to attach this buffer at the start or end of free list
  if (isInState(buffer, BUFFER_DATA_VALID) & !isInState(buffer, BUFFER_DATA_OLD)) {
    freeList_push_back(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  } else {
    freeList_push_front(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  }
  
  // lower_cpu_level();
  printf("Lowering CPU level to allow interrupts.\n");

  // release buffer
  printf("RELEASING BUFFER.\nAdding Buffer to Freelist. \n");

  if(isWaitingQueueEmpty()){
    printf("No Process was waiting. So no race condition.");
    return;
  }

  printf("Woken Up processes now race to obtain this free buffer.\n");  
  int blk_num = getProcessFromWaitingQueue(buffer->blockNumber);
  
  printf("Running getblk for this process with block number %d\n", blk_num);
  Buffer *allocatedBuffer = getblk(blk_num);
  if(allocatedBuffer != NULL){
    	printf("Buffer Allocated Successfully.\n");
  }
  return;
}
