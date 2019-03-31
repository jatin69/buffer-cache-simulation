#include "./bufferCache.h"

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

Buffer *getFreeListHead() {
  Buffer *ret = freeListHead.free_next;
  return ret;
}

Buffer *remove_free_head() {
  if (isFreeListEmpty()) {
    return NULL;
  }
  Buffer *ret = freeListHead.free_next;
  while (CheckStatus(ret, STAT_DWR)) {
    if (ret == &freeListHead) {
      printf("Oops somethig wrong happening here\n");
      return NULL;
    }
    ret = ret->free_next;
  }

  remove_hash(ret);
  freeListHead.free_next = freeListHead.free_next->free_next;
  freeListHead.free_next->free_prev = &freeListHead;
  return ret;
}

int isFreeListEmpty() {
  if (freeListHead.free_next == &freeListHead &&
      freeListHead.free_prev == &freeListHead) {
    return 1;
  }
  return 0;
}

void removeBufferFromFreeList(Buffer *buffer) {
  Buffer *prev = buffer->free_prev;
  Buffer *next = buffer->free_next;
  prev->free_next = next;
  next->free_prev = prev;
  buffer->free_next = NULL;
  buffer->free_prev = NULL;
}

int isInFreeList(Buffer *buffer) {
  for (Buffer *p = &freeListHead; p != &freeListHead; p = p->free_next) {
    if (p == buffer) {
      return p->blockNumber;
    }
  }
  return 0;
}

