#include "./bufferCache.h"

void PrintRoutine(Buffer *p, int index) {
  if (index >= 10) {
    if (p->blockNumber >= 100) {
      printf("[%d : D%d ", index, p->blockNumber);
    } else {
      if (p->blockNumber >= 10) {
        printf("[%d :  D%d ", index, p->blockNumber);
      } else {
        printf("[%d :   D%d ", index, p->blockNumber);
      }
    }
  } else {
    if (p->blockNumber >= 10) {
      if (p->blockNumber >= 100) {
        printf("[ %d : D%d ", index, p->blockNumber);
      } else {
        printf("[ %d :  D%d ", index, p->blockNumber);
      }
    } else {
      printf("[ %d :   D%d ", index, p->blockNumber);
    }
  }
}

void PrintState(Buffer *p) {
  int state = p->status;
  if (state & 0x20)
    printf("O");
  else
    printf("-");
  state = state << 1;

  if (state & 0x20)
    printf("W");
  else
    printf("-");
  state = state << 1;

  if (state & 0x20)
    printf("K");
  else
    printf("-");
  state = state << 1;

  if (state & 0x20)
    printf("D");
  else
    printf("-");
  state = state << 1;

  if (state & 0x20)
    printf("V");
  else
    printf("-");
  state = state << 1;

  if (state & 0x20)
    printf("L");
  else
    printf("-");
}

void PrintBufferOne(int index) {
  int hkey = index / 3;
  Buffer *p = hashQueue[hkey];
  for (int i = index % 3; i >= 0; i--) {
    p = p->hash_next;
  }
  PrintRoutine(p, index);
  // printf("[ %d : %d ", index, p -> blockNumber);
  PrintState(p);
  printf("]\n");
}

void PrintBufferAll() {
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    for (Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
      PrintRoutine(p, index);
      PrintState(p);
      printf("]\n");
      index++;
    }
  }
}

void PrintHashLine(int hkey) {
  int index = hkey * 3;
  for (Buffer *p = hashQueue[hkey]->hash_next; p != hashQueue[hkey]; p = p->hash_next) {
    // printf("\t[ %d : %d ", index, p -> blockNumber);
    PrintRoutine(p, index);
    PrintState(p);
    printf("]  ");
    index++;
  }
  printf("\n");
}

void PrintHashAll() {
  // printf("Hash[n ...]\n");
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    printf("%d  :", i);
    for (Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
      // printf("\t[ %d : %d ", index, p -> blockNumber);
      PrintRoutine(p, index);
      PrintState(p);
      printf("]");
      index++;
    }
    printf("\n");
  }
}

int SearchNum(int blockNumber) {
  Buffer *buffer = searchBufferInHashQueue(blockNumber);
  int index = 0;
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    for (Buffer *p = hashQueue[i]->hash_next; p != hashQueue[i]; p = p->hash_next) {
      if (p == buffer)
        return index;
      index++;
    }
  }
  return index;
}


void PrintFree() {
  int index = 0;
  for (Buffer *p = freeListDummyHead->free_next; p != freeListDummyHead; p = p->free_next) {
    index = SearchNum(p->blockNumber);
    PrintRoutine(p, index);
    // printf("\t[ %d : %d ", index, p -> blockNumber);
    PrintState(p);
    printf("]");
  }
  printf("\n");
}

