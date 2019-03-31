#include "./bufferCache.h"

Buffer *Clone(int blockNumber) {
  int hkey = blockNumber % 4;
  Buffer *p;
  for (p = hashQueue[hkey].hash_next; p != &hashQueue[hkey]; p = p->hash_next) {
    if (p->blockNumber == blockNumber) {
      return p;
    }
  }
  if (p == NULL) {
    printf("Invalid block number, There is no such block number in cache\n");
  }
  return NULL;
}
