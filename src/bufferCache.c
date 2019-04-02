#include "./bufferCache.h"

/************************** isEmpty **************************/

/**Check if the hash queue is empty
 * 
 * i.e. only dummy head left in the list
*/
int isHashQueueEmpty(int key) {
  key %= NO_OF_HASH_QUEUES;
  if (hashQueue[key]->hash_next == hashQueue[key] &&
      hashQueue[key]->hash_prev == hashQueue[key]) {
    return 1;
  }
  return 0;
}

/**Check if free list is empty
 * 
 * i.e. only dummy head left in the list
*/
int isFreeListEmpty() {
  if (freeListDummyHead->free_next == freeListDummyHead &&
      freeListDummyHead->free_prev == freeListDummyHead) {
    return 1;
  }
  return 0;
} 

/************************** Search **************************/

/**Search Block in Hash Queue.
 * 
 * Return that buffer if found.
 * Return NULL if not found.
*/
Buffer *searchBlockInHashQueue(int blk_num) {
  int hash_key = blk_num % NO_OF_HASH_QUEUES;
  Buffer *p;
  for (p = hashQueue[hash_key]->hash_next; p != hashQueue[hash_key]; p = p->hash_next)
    if (p->blockNumber == blk_num)
      return p;

  return NULL;
}

/**check if a particular buffer exists in free list
 * 
 * Return 1 if it exists in free list
 * Return 0 if it does not exists in free list
*/
int searchBufferInFreeList(Buffer *buffer) {
  int found = 0;
  for (Buffer *p = freeListDummyHead->free_next; p != freeListDummyHead; p = p->free_next) {
    if (p == buffer) {  found = 1; break; }
  }
  return found;
}

/************************ Add to Front ************************/

/**Hash Queue add to front
 * 
 * Add `buffer` immediately after the dummyHead of this hash queue
*/
void hashQueue_push_front(Buffer *dummyHead, Buffer *buffer) {
  buffer->hash_prev = dummyHead;
  buffer->hash_next = dummyHead->hash_next;
  dummyHead->hash_next->hash_prev = buffer;
  dummyHead->hash_next = buffer;
} 

/**Free List add to front
 * 
 * Add `buffer` immediately after the dummyHead of the freeList
*/
void freeList_push_front(Buffer *dummyHead, Buffer *buffer) {
  buffer->free_prev = dummyHead;
  buffer->free_next = dummyHead->free_next;
  dummyHead->free_next->free_prev = buffer;
  dummyHead->free_next = buffer;
}

/************************ Add to Back ************************/

/**Hash Queue add to tail
 * 
 * Add `buffer` to tail of the queue who head is `dummyHead`
*/
void hashQueue_push_back(Buffer *dummyHead, Buffer *buffer) {
  buffer->hash_next = dummyHead;
  buffer->hash_prev = dummyHead->hash_prev;
  dummyHead->hash_prev->hash_next = buffer;
  dummyHead->hash_prev = buffer;
}

/**Free List add to tail
 * 
 * Add `buffer` to tail of the list who head is `dummyHead`
*/
void freeList_push_back(Buffer *dummyHead, Buffer *buffer) {
  buffer->free_next = dummyHead;
  buffer->free_prev = dummyHead->free_prev;
  dummyHead->free_prev->free_next = buffer;
  dummyHead->free_prev = buffer;
}

/************************ Add ************************/

/**Add `buffer` to the head appropriate HashQueue
 * 
*/
void addBufferToHashQueue(Buffer *buffer) {
  int key = buffer->blockNumber % NO_OF_HASH_QUEUES;
  addState(buffer, BUFFER_BUSY);
  hashQueue_push_back(hashQueue[key], buffer);
}

/**Add `buffer` to free list
 * 
*/
void addBufferToFreeList(Buffer *buffer) {
  removeState(buffer, BUFFER_BUSY);
  freeList_push_back(freeListDummyHead, buffer);
}


/************************ Remove ************************/

/**Remove a buffer from the hash queue
 * 
 * This is possible without any dummyHead because it is a doubly linkedlist
*/
void removeBufferFromHashQueue(Buffer *buffer) {
  Buffer *next = buffer->hash_next;
  Buffer *prev = buffer->hash_prev;
  prev->hash_next = next;
  next->hash_prev = prev;
  buffer->hash_next = NULL;
  buffer->hash_prev = NULL;
}

/**Remove a buffer from free list
 * 
 * because it is now busy.
*/
void removeBufferFromFreeList(Buffer *buffer) {
  Buffer *next = buffer->free_next;
  Buffer *prev = buffer->free_prev;
  prev->free_next = next;
  next->free_prev = prev;
  buffer->free_next = NULL;
  buffer->free_prev = NULL;
}

/************************ Get buffer ************************/

/**Remove a free Buffer from head of Free list
 * 
 * Steps - 
 * traverse the free list starting from head
 * Skip a buffer if it is marked delayed write
 * free buffer found
 * remove it from old hash queue
 * remove it from free list
 * return it
 * 
*/
Buffer *getBufferFromHeadOfFreeList() {
  if (isFreeListEmpty()) {
    return NULL;
  }
  Buffer *ret = freeListDummyHead->free_next;
  while (isInState(ret, BUFFER_MARKED_DELAYED_WRITE)) {
    ret = ret->free_next;
  }
  removeBufferFromHashQueue(ret);
  freeListDummyHead->free_next = freeListDummyHead->free_next->free_next;
  freeListDummyHead->free_next->free_prev = freeListDummyHead;
  return ret;
}
