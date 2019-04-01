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
  // raise_cpu_level();
  if (isInState(buffer, BUFFER_DATA_VALID) & !isInState(buffer, BUFFER_DATA_OLD)) {
    // insert_list(&freeListDummyHead, buffer, FREETAIL);
    freeList_push_back(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  } else {
    // insert_list(&freeListDummyHead, buffer, FREEHEAD);
    freeList_push_front(freeListDummyHead, buffer);
    setState(buffer, BUFFER_DATA_VALID);
  }

  // lower_cpu_level();
}
