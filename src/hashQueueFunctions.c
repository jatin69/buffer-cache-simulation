#include "./bufferCache.h"

int isHashQueueEmpty(int hashQueueNumber) {
  hashQueueNumber %= 4;
  if (hashQueue[hashQueueNumber]->hash_next == hashQueue[hashQueueNumber] &&
      hashQueue[hashQueueNumber]->hash_prev == hashQueue[hashQueueNumber]) {
    return 1;
  }
  return 0;
}

void hashQueue_push_front(Buffer *head, Buffer *buf) {
  buf->hash_prev = head;
  buf->hash_next = head->hash_next;
  head->hash_next->hash_prev = buf;
  head->hash_next = buf;
}

void hashQueue_push_back(Buffer *head, Buffer *buf) {
  buf->hash_next = head;
  buf->hash_prev = head->hash_prev;
  head->hash_prev->hash_next = buf;
  head->hash_prev = buf;
}

void addBufferToHashQueue(Buffer *buf) {
  int key = buf->blockNumber % 4;
  addState(buf, BUFFER_BUSY);
  hashQueue_push_back(hashQueue[key], buf);
}

void removeBufferFromHashQueue(Buffer *buf) {
  Buffer *prev = buf->hash_prev;
  Buffer *next = buf->hash_next;
  prev->hash_next = buf->hash_next;
  next->hash_prev = prev;
}

Buffer *searchBlockInHashQueue(int num) {
  int hash_key = num % 4;
  Buffer *p;
  for (p = hashQueue[hash_key]->hash_next; p != hashQueue[hash_key]; p = p->hash_next)
    if (p->blockNumber == num)
      return p;

  return NULL;
}