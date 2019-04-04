#include "./bufferCache.h"

// print Buffer with index, data and status
void printBuffer(int index, Buffer *p) {
  printf("[");
  printf("%3d : D%3d ", index, p->blockNumber);
  (p->status & BUFFER_DATA_OLD)             ? printf("O") : printf("-");
  (p->status & BUFFER_AWAITED)              ? printf("W") : printf("-");
  (p->status & KERNEL_READING_WRITING)      ? printf("K") : printf("-");
  (p->status & BUFFER_MARKED_DELAYED_WRITE) ? printf("D") : printf("-");
  (p->status & BUFFER_DATA_VALID)           ? printf("V") : printf("-");
  (p->status & BUFFER_BUSY)                 ? printf("B") : printf("-");
  printf("]");
}

// print all buffers
void printAllBuffers() {
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    Buffer *buf = hashQueue[i]->hash_next;
    while(buf != hashQueue[i]) {
      printBuffer(index, buf);
      printf("\n");
      buf = buf->hash_next;      
      index++;
    }
  }
}

// print all hash Queues
void printAllHashQueues() {
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    printf("%d  :", i);
    for (Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
      printBuffer(index, p);
      index++;
    }
    printf("\n");
  }
}

int getIndexOfBuffer(Buffer *buf){
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    for (Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
      if(buf == p){
        return index;
      }
      index++;
    }
  }
  return -1;
}

// print free list 
void printFreeList() {
  for(Buffer *p = freeListDummyHead->free_next; p != freeListDummyHead; p = p->free_next) {
    Buffer *buf = searchBlockInHashQueue(p->blockNumber); 
    printBuffer(getIndexOfBuffer(buf), buf);
  }
  printf("\n");
}

// print status
void printState(Buffer *p) {
  (p->status & BUFFER_DATA_OLD)             ? printf("O") : printf("-");
  (p->status & BUFFER_AWAITED)              ? printf("W") : printf("-");
  (p->status & KERNEL_READING_WRITING)      ? printf("K") : printf("-");
  (p->status & BUFFER_MARKED_DELAYED_WRITE) ? printf("D") : printf("-");
  (p->status & BUFFER_DATA_VALID)           ? printf("V") : printf("-");
  (p->status & BUFFER_BUSY)                 ? printf("B") : printf("-");
}

// print waiting queue
void printWaitingQueue() {
  int pcount = 1;
  for(int i=0; i<SIZE_OF_WAITING_QUEUE; ++i) {
    if(waitingQueue[i] > 0){
      printf("[ getblk %d : %s] ", waitingQueue[i], "WAITING FOR ANY BUFFER");
      pcount++;
    }
    else if(waitingQueue[i] < 0){
      printf("[ getblk %d : %s] ", waitingQueue[i]*-1, "WAITING FOR THIS BUFFER");
      pcount++;
    }
    if(pcount % 4 ==0){
      printf("\n");
    }
  }
  printf("\n");
}

