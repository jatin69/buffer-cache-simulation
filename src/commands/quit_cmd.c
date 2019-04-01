#include "./../bufferCache.h"
#include "./../externVariables.h"

void quit_cmd(int argc, char *argv[]) {
  if (bufferHasBeenInitialised) {
    for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
      Buffer *trav = hashQueue[i];
      while (!isHashQueueEmpty(i)) {
        Buffer *ret = hashQueue[i]->hash_next;
        removeBufferFromHashQueue(ret);
        free(ret);
      }
    }

    while(!isFreeListEmpty()){
      Buffer* target = removeBufferFromHeadOfFreeList();
      free(target);
    }
  }
  exit(0);
}
