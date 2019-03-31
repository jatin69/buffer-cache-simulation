#include "./bufferCache.h"

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

void remove_hash(Buffer *buf) {
  Buffer *prev = buf->hash_prev;
  Buffer *next = buf->hash_next;
  prev->hash_next = buf->hash_next;
  next->hash_prev = prev;
}

Buffer *remove_hash_head(int i) {
  Buffer *ret = hashQueue[i].hash_next;
  remove_hash(ret);
  return ret;
}

int isHashQueueEmpty(int hashQueueNumber) {
  hashQueueNumber %= 4;
  if (hashQueue[hashQueueNumber].hash_next == &hashQueue[hashQueueNumber] &&
      hashQueue[hashQueueNumber].hash_prev == &hashQueue[hashQueueNumber]) {
    return 1;
  }
  return 0;
}

Buffer *searchBufferInHashQueue(int num) {
  int hash_key = num % 4;
  Buffer *p;
  for (p = hashQueue[hash_key].hash_next; p != &hashQueue[hash_key]; p = p->hash_next)
    if (p->blockNumber == num)
      return p;

  return NULL;
}

void addToHashQueue(Buffer *elem) {
  int key = elem->blockNumber;
  int hkey = key % 4;
  AddStatus(elem, STAT_LOCKED);
  hashQueue_push_back(&hashQueue[hkey], elem);
  // insert_list(&hashQueue[hkey], elem, HASHTA IL);
}
