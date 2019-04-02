#include "./bufferCache.h"

void brelse(Buffer *buffer) {
  if(buffer == NULL){
    return;
  }
  // wakeup();
  printf("Wakeup processes wating for any buffer\n");
  if (isInState(buffer, BUFFER_BUSY | BUFFER_DATA_VALID | BUFFER_AWAITED)) {
    // wakeup();
    printf("Wakeup processes waiting for buffer of blockNumber %d\n", buffer->blockNumber);
  }
  printf("Raising CPU level to block interrupts.\n");
  // raise_cpu_level();

  if (isInState(buffer, BUFFER_DATA_VALID) & !isInState(buffer, BUFFER_DATA_OLD)) {
    freeList_push_back(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  } else {
    freeList_push_front(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  }
  
  printf("Lowering CPU level to allow interrupts.\n");
  // lower_cpu_level();
  printf("RELEASING BUFFER.\nAdding Buffer to Freelist. \n");

  if(isWaitingQueueEmpty()){
    printf("NO Process was waiting. So no race condition.");
    return;
  }

  // Then this
  printf("Woken Up processes now race to obtain this free buffer.\n");
  // randomly any of the woken up process wins
  
  int blk_num = getProcessFromWaitingQueue(buffer->blockNumber);
  
  printf("RUNNING getblk for this process with block number %d\n", blk_num);
  Buffer *allocatedBuffer = getblk(blk_num);
  return;
}
