#ifndef SRC_BUFFER_CACHE_H
#define SRC_BUFFER_CACHE_H

// standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


// Buffer Header Structure
typedef struct BufferHeader {
  int deviceNumber;
  int blockNumber;
  unsigned int status;
  char *cache_data;
  
  struct BufferHeader *hash_next;
  struct BufferHeader *hash_prev;
  struct BufferHeader *free_next;
  struct BufferHeader *free_prev;
  
} Buffer;

// Possible states for a Buffer
typedef enum STATE {

  // Is buffer currently in use by a process
  BUFFER_BUSY = 1,

  // Is buffer data valid
  BUFFER_DATA_VALID = 2,

  // Is buffer marked delayed write
  BUFFER_MARKED_DELAYED_WRITE = 4,

  // Is kernel currently reading/writing this buffer to memory
  KERNEL_READING_WRITING = 8, 

  // Is another process waiting for this buffer
  BUFFER_AWAITED = 16,  

  // Is this Buffer's data OLD
  BUFFER_DATA_OLD = 32

} STATE;

// STATE Manipulation
void addState(Buffer *buffer, STATE state);
void removeState(Buffer *buffer, STATE state);
void setState(Buffer *buffer, STATE state);
int isInState(Buffer *buffer, STATE state);

// Waiting Queue : for sleeping processes waiting for a buffer to get free
#define SIZE_OF_WAITING_QUEUE 10
int* waitingQueue;

// Types of waiting
typedef enum WAITING_TYPE{
  WAITING_FOR_THIS_BUFFER = -1,   // negative for THIS buffer
  WAITING_FOR_ANY_BUFFER = 1      // positive for ANY buffer
} WAITING_TYPE;

// Managing waiting Queue
void addToWaitingQueue(int blk_num, WAITING_TYPE WAITING_FOR_THIS_BUFFER);
int findInWaitingQueue(int blockNumber);
int getProcessFromWaitingQueue(int blockNumber);
int isWaitingQueueEmpty();

// Doubly Linked List for Hash Queue's and Free List

#define NO_OF_HASH_QUEUES 4

// pointer to an array of Hash Queue Pointers
Buffer** hashQueue;

// Free List Head
Buffer* freeListDummyHead;

// Hash Queue functions
int isHashQueueEmpty(int hashQueueNumber);

void hashQueue_push_front(Buffer *ref, Buffer *buf);
void hashQueue_push_back(Buffer *ref, Buffer *buf);

void addBufferToHashQueue(Buffer *buf);
void removeBufferFromHashQueue(Buffer *buf);

Buffer *searchBlockInHashQueue(int blockNumber);


// Free List functions
int isFreeListEmpty();

void freeList_push_front(Buffer *ref, Buffer *buf);
void freeList_push_back(Buffer *ref, Buffer *buf);

Buffer *getBufferFromHeadOfFreeList();
void removeBufferFromFreeList(Buffer*);

int searchBufferInFreeList(Buffer *buffer);

// pretty printing functions
void printBuffer(int index, Buffer *p);
void printAllBuffers();
void printAllHashQueues();
void printFreeList();
void printWaitingQueue();


// Buffer Cache Management Algorithms
Buffer *getblk(int blk_num);    // getblock
void brelse(Buffer *buffer);    // release block

#endif // !SRC_BUFFER_CACHE_H