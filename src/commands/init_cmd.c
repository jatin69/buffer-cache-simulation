#include "./../bufferCache.h"
#include "./../externVariables.h"

void init_cmd(int argc, char *argv[]) {
  
  // if already initialised, free it all up
  if (initnum) {
    for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
      while (!isHashQueueEmpty(i)) {
        Buffer *ret = remove_hash_head();
        free(ret);
      }
    }
    initnum = 0;
  }

  // reinitialise everything
  initnum = 1;
  malloced = 1;
  
  // loop all hashQueues
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    
    // empty out the hashQueue, set to defaults
    hashQueue[i].hash_next = &hashQueue[i];
    hashQueue[i].hash_prev = &hashQueue[i];
    hashQueue[i].status = 0;
    hashQueue[i].free_next = &freeListHead;
    hashQueue[i].free_prev = &freeListHead;
    hashQueue[i].cache_data = NULL;
    
    // put 3 buffers in each hash queue
    Buffer *p = malloc(sizeof(Buffer));
    Buffer *q = malloc(sizeof(Buffer));
    Buffer *r = malloc(sizeof(Buffer));
    if (p == NULL || q == NULL || r == NULL) {
      printf("unable to assign memory\n");
      abort();
    }

    hashQueue_push_front(&hashQueue[i], p);
    hashQueue_push_front(hashQueue[i].hash_next, q);
    hashQueue_push_front(((hashQueue[i].hash_next)->hash_next), r);
    
    // insert_list(&hashQueue[i], p, HASHHEAD);
    // insert_list(hashQueue[i].hash_next, q, HASHHEAD);
    // insert_list(((hashQueue[i].hash_next)->hash_next), r, HASHHEAD);
  }

  freeListHead.free_next = &freeListHead;
  freeListHead.free_prev = &freeListHead;
  Buffer *trac = hashQueue[0].hash_next;
  trac->blockNumber = 28;
  SetStatus(trac, STAT_VALID);
  trac = trac->hash_next;
  trac->blockNumber = 4;
  SetStatus(trac, STAT_VALID);
  trac = trac->hash_next;
  trac->blockNumber = 64;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);
  // mod = 1
  trac = hashQueue[1].hash_next;
  trac->blockNumber = 17;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);
  trac = trac->hash_next;
  trac->blockNumber = 5;
  SetStatus(trac, STAT_VALID);
  trac = trac->hash_next;
  trac->blockNumber = 97;
  SetStatus(trac, STAT_VALID);
  // mod = 2
  trac = hashQueue[2].hash_next;
  trac->blockNumber = 98;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);
  trac = trac->hash_next;
  trac->blockNumber = 50;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);
  trac = trac->hash_next;
  trac->blockNumber = 10;
  SetStatus(trac, STAT_VALID);
  // mod = 3
  trac = hashQueue[3].hash_next;
  trac->blockNumber = 3;
  SetStatus(trac, STAT_VALID);
  trac = trac->hash_next;
  trac->blockNumber = 35;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);
  trac = trac->hash_next;
  trac->blockNumber = 99;
  SetStatus(trac, STAT_VALID | STAT_LOCKED);

  // adding freelist
  trac = &freeListHead;

  freeList_push_back(&freeListHead, hashQueue[3].hash_next);
  freeList_push_back(&freeListHead, hashQueue[1].hash_next->hash_next);
  freeList_push_back(&freeListHead, hashQueue[0].hash_next->hash_next);
  freeList_push_back(&freeListHead, hashQueue[0].hash_next);
  freeList_push_back(&freeListHead, hashQueue[1].hash_next->hash_next->hash_next);
  freeList_push_back(&freeListHead, hashQueue[2].hash_next->hash_next->hash_next);
  
  // insert_list(trac, hashQueue[3].hash_next, FREETAIL);
  // insert_list(trac, hashQueue[1].hash_next->hash_next, FREETAIL);
  // insert_list(trac, hashQueue[0].hash_next->hash_next, FREETAIL);
  // insert_list(trac, hashQueue[0].hash_next, FREETAIL);
  // insert_list(trac, hashQueue[1].hash_next->hash_next->hash_next, FREETAIL);
  // insert_list(trac, hashQueue[2].hash_next->hash_next->hash_next, FREETAIL);
  
}