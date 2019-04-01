#include "./../bufferCache.h"
#include "./../externVariables.h"

void init_cmd(int argc, char *argv[]) {
  
  // if already initialised, free it all up
  if (initnum) {
    // @todo
    // for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {
    //   while (!isHashQueueEmpty(i)) {
    //     Buffer *ret = remove_hash_head();
    //     free(ret);
    //   }
    // }
    initnum = 0;
  }

  // reinitialise everything
  initnum = 1;
  malloced = 1;

  hashQueue =  (Buffer **)malloc(sizeof(Buffer *) * NO_OF_HASH_QUEUES);
  

  // for(int i=0;i<NO_OF_HASH_QUEUES;i++){
  //   hashQueue[i]=(Buffer *)malloc(sizeof(Buffer)*3);
  // }
  // loop all hashQueues
  for (int i = 0; i < NO_OF_HASH_QUEUES; i++) {

    // dummy head
    hashQueue[i] = (Buffer*)malloc(sizeof(Buffer));
    
    // empty out the hashQueue, set to defaults
    hashQueue[i]->hash_next = hashQueue[i];
    hashQueue[i]->hash_prev = hashQueue[i];
    hashQueue[i]->status = 0;
    hashQueue[i]->free_next = freeListDummyHead;
    hashQueue[i]->free_prev = freeListDummyHead;
    hashQueue[i]->cache_data = NULL;
    
    // put 3 buffers in each hash queue
    Buffer *p = malloc(sizeof(Buffer));
    hashQueue_push_front(hashQueue[i], p);
    
    Buffer *q = malloc(sizeof(Buffer));
    hashQueue_push_front(hashQueue[i]->hash_next, q);
    
    Buffer *r = malloc(sizeof(Buffer));
    hashQueue_push_front(hashQueue[i]->hash_next->hash_next, r);
    
    // insert_list(&hashQueue[i], p, HASHHEAD);
    // insert_list(hashQueue[i].hash_next, q, HASHHEAD);
    // insert_list(((hashQueue[i].hash_next)->hash_next), r, HASHHEAD);
  }

  Buffer *trav;

  // Setting up hash Queue 0
  trav = hashQueue[0]->hash_next;
  trav->blockNumber = 28;
  SetStatus(trav, STAT_VALID);

  trav = trav->hash_next;
  trav->blockNumber = 4;
  SetStatus(trav, STAT_VALID);

  trav = trav->hash_next;
  trav->blockNumber = 64;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);

  // Setting up hash Queue 1
  trav = hashQueue[1]->hash_next;
  trav->blockNumber = 17;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);
  
  trav = trav->hash_next;
  trav->blockNumber = 5;
  SetStatus(trav, STAT_VALID);
  
  trav = trav->hash_next;
  trav->blockNumber = 97;
  SetStatus(trav, STAT_VALID);
  
  // Setting up hash Queue 2
  trav = hashQueue[2]->hash_next;
  trav->blockNumber = 98;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);
  trav = trav->hash_next;
  
  trav->blockNumber = 50;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);
  trav = trav->hash_next;
  
  trav->blockNumber = 10;
  SetStatus(trav, STAT_VALID);
  
  // Setting up hash Queue 3
  trav = hashQueue[3]->hash_next;
  trav->blockNumber = 3;
  SetStatus(trav, STAT_VALID);
  
  trav = trav->hash_next;
  trav->blockNumber = 35;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);
  
  trav = trav->hash_next;
  trav->blockNumber = 99;
  SetStatus(trav, STAT_VALID | STAT_LOCKED);

  // adding freelist
  // trav = freeListDummyHead;

// allocate memory for free List - dummy head
  freeListDummyHead = (Buffer*)malloc(sizeof(Buffer));
  freeListDummyHead->free_next = freeListDummyHead;
  freeListDummyHead->free_prev = freeListDummyHead;

  freeList_push_back(freeListDummyHead, hashQueue[3]->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[1]->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[0]->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[0]->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[1]->hash_next->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[2]->hash_next->hash_next->hash_next);
  
  // insert_list(trav, hashQueue[3].hash_next, FREETAIL);
  // insert_list(trav, hashQueue[1].hash_next->hash_next, FREETAIL);
  // insert_list(trav, hashQueue[0].hash_next->hash_next, FREETAIL);
  // insert_list(trav, hashQueue[0].hash_next, FREETAIL);
  // insert_list(trav, hashQueue[1].hash_next->hash_next->hash_next, FREETAIL);
  // insert_list(trav, hashQueue[2].hash_next->hash_next->hash_next, FREETAIL);
  
}