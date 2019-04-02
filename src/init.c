#include "./bufferCache.h"

/**
 * Initialise Buffer Cache to Fig 3.3
 */
void init() {
  
  printf("Initialising ...\n");
  printf("Creating Hash Queues ... ");
  hashQueue =  (Buffer **)malloc(sizeof(Buffer *) * NO_OF_HASH_QUEUES);
  
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

  }
  printf("Done\n");

  // allocate memory for free List - dummy head
  printf("Creating Free List ... ");
  freeListDummyHead = (Buffer*)malloc(sizeof(Buffer));
  freeListDummyHead->free_next = freeListDummyHead;
  freeListDummyHead->free_prev = freeListDummyHead;
  printf("Done\n");


  Buffer *trav;

  printf("Setting up Buffer Cache as per figure 3.2 of Maurice J Bach\n");
  
  printf("Setting up Hash Queues ... ");
  // Setting up hash Queue 0
  trav = hashQueue[0]->hash_next;
  trav->blockNumber = 28;
  setState(trav, BUFFER_DATA_VALID);

  trav = trav->hash_next;
  trav->blockNumber = 4;
  setState(trav, BUFFER_DATA_VALID);

  trav = trav->hash_next;
  trav->blockNumber = 64;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);

  // Setting up hash Queue 1
  trav = hashQueue[1]->hash_next;
  trav->blockNumber = 17;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);
  
  trav = trav->hash_next;
  trav->blockNumber = 5;
  setState(trav, BUFFER_DATA_VALID);
  
  trav = trav->hash_next;
  trav->blockNumber = 97;
  setState(trav, BUFFER_DATA_VALID);
  
  // Setting up hash Queue 2
  trav = hashQueue[2]->hash_next;
  trav->blockNumber = 98;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);
  trav = trav->hash_next;
  
  trav->blockNumber = 50;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);
  trav = trav->hash_next;
  
  trav->blockNumber = 10;
  setState(trav, BUFFER_DATA_VALID);
  
  // Setting up hash Queue 3
  trav = hashQueue[3]->hash_next;
  trav->blockNumber = 3;
  setState(trav, BUFFER_DATA_VALID);
  
  trav = trav->hash_next;
  trav->blockNumber = 35;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);
  
  trav = trav->hash_next;
  trav->blockNumber = 99;
  setState(trav, BUFFER_DATA_VALID | BUFFER_BUSY);
  printf("Done\n");

  
  printf("Setting up Free List ... ");
  freeList_push_back(freeListDummyHead, hashQueue[3]->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[1]->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[0]->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[0]->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[1]->hash_next->hash_next->hash_next);
  freeList_push_back(freeListDummyHead, hashQueue[2]->hash_next->hash_next->hash_next);
  printf("Done\n");

  printf("Setting up Wait Queue ... ");
  waitingQueue = (int*)malloc(sizeof(int)*SIZE_OF_WAITING_QUEUE);
  printf("Done\n");

  printf("Ready to go.\n");
}