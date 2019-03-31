#include "./../bufferCache.h"
#include "./../externVariables.h"

void quit_cmd(int argc, char *argv[]) {
  if (malloced) {
    for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
      // Buffer *trac = &hashQueue[i];
      while (!isHashQueueEmpty(i)) {
        Buffer *ret = remove_hash_head();
        free(ret);
      }
    }
  }
  exit(0);
}
