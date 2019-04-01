#include "./bufferCache.h"

void brelse(Buffer *buffer) {
  if(buffer == NULL){
    return;
  }
  // wakeup();
  printf("Wakeup processes wating for any buffer\n");
  if (CheckStatus(buffer, STAT_LOCKED | STAT_VALID | STAT_WAITED)) {
    // wakeup();
    printf("Wakeup processes waiting for buffer of blockNumber %d\n", buffer->blockNumber);
  }
  // raise_cpu_level();
  if (CheckStatus(buffer, STAT_VALID) & !CheckStatus(buffer, STAT_OLD)) {
    // insert_list(&freeListDummyHead, buffer, FREETAIL);
    freeList_push_back(freeListDummyHead, buffer);
    MakeStatus(buffer, STAT_VALID);
  } else {
    // insert_list(&freeListDummyHead, buffer, FREEHEAD);
    freeList_push_front(freeListDummyHead, buffer);
    MakeStatus(buffer, STAT_VALID);
  }

  // lower_cpu_level();
}
