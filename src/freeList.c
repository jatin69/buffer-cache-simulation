#include "./bufferCache.h"

int isFreeListEmpty() {
  if (freeListDummyHead->free_next == freeListDummyHead &&
      freeListDummyHead->free_prev == freeListDummyHead) {
    return 1;
  }
  return 0;
}

void freeList_push_front(Buffer *head, Buffer *buf) {
  buf->free_prev = head;
  buf->free_next = head->free_next;
  head->free_next->free_prev = buf;
  head->free_next = buf;
}

void freeList_push_back(Buffer *head, Buffer *buf) {
  buf->free_next = head;
  buf->free_prev = head->free_prev;
  head->free_prev->free_next = buf;
  head->free_prev = buf;
}

Buffer *removeBufferFromHeadOfFreeList() {
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


void removeBufferFromFreeList(Buffer *buffer) {
  Buffer *prev = buffer->free_prev;
  Buffer *next = buffer->free_next;
  prev->free_next = next;
  next->free_prev = prev;
  buffer->free_next = NULL;
  buffer->free_prev = NULL;
}

int searchBufferInFreeList(Buffer *buffer) {
  for (Buffer *p = freeListDummyHead->free_next; p != freeListDummyHead; p = p->free_next) {
    if (p == buffer) {
      return 1;
    }
  }
  return 0;
}

