#include "./bufferCache.h"

void printBuffer(int index, Buffer *p) {
  printf("[");
  printf("%3d : D%3d ", index, p->blockNumber);
  (p->status & BUFFER_DATA_OLD)             ? printf("O") : printf("-");
  (p->status & BUFFER_AWAITED)              ? printf("W") : printf("-");
  (p->status & KERNEL_READING_WRITING)      ? printf("K") : printf("-");
  (p->status & BUFFER_MARKED_DELAYED_WRITE) ? printf("D") : printf("-");
  (p->status & BUFFER_DATA_VALID)           ? printf("V") : printf("-");
  (p->status & BUFFER_DATA_OLD)             ? printf("L") : printf("-");
  printf("]");
}

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

void printFreeList() {
  int flag = 1;
  for(Buffer *p = freeListDummyHead->free_next; p != freeListDummyHead; p = p->free_next) {
    Buffer *buf = searchBlockInHashQueue(p->blockNumber); 
    int index = 0;
    for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
      for(Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
        if (p == buf) {  flag=1;  break; }
        ++index;
      }
      if(flag){ break;  }
    }
    printBuffer(index, p);
  }
  printf("\n");
}

void printState(Buffer *p) {
  int state = p->status;
  (p->status & BUFFER_DATA_OLD)             ? printf("O") : printf("-");
  (p->status & BUFFER_AWAITED)              ? printf("W") : printf("-");
  (p->status & KERNEL_READING_WRITING)      ? printf("K") : printf("-");
  (p->status & BUFFER_MARKED_DELAYED_WRITE) ? printf("D") : printf("-");
  (p->status & BUFFER_DATA_VALID)           ? printf("V") : printf("-");
  (p->status & BUFFER_DATA_OLD)             ? printf("L") : printf("-");
}
