#ifndef SRC_BUFFER_CACHE_H
#define SRC_BUFFER_CACHE_H

// standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>


/** Buffer Header Structure
 */

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

/**Global Objects
 * 
*/

typedef enum STATE {
  BUFFER_BUSY = 1,
  BUFFER_DATA_VALID = 2,
  BUFFER_MARKED_DELAYED_WRITE = 4,
  KERNEL_READING_WRITING = 8, // Is kernel currently reading/writing this buffer to memory
  BUFFER_AWAITED = 16,  // Is another process waiting for this buffer
  BUFFER_DATA_OLD = 32
} STATE;

// STATE Manipulation
void addState(Buffer *buffer, STATE state);
void removeState(Buffer *buffer, STATE state);
void setState(Buffer *buffer, STATE state);
int isInState(Buffer *buffer, STATE state);

#define SIZE_OF_WAITING_QUEUE 10
int* waitingQueue;

typedef enum WAITING_TYPE{
  WAITING_FOR_THIS_BUFFER = -1,   // negative for this buffer
  WAITING_FOR_ANY_BUFFER = 1      // positive for any buffer
} WAITING_TYPE;

void addToWaitingQueue(int blk_num, WAITING_TYPE WAITING_FOR_THIS_BUFFER);
int getProcessFromWaitingQueue(int blockNumber);
int isWaitingQueueEmpty();
void printWaitingQueue();

/**Doubly Linked List Management
 * 
*/
#define NO_OF_HASH_QUEUES 4

Buffer** hashQueue;
Buffer* freeListDummyHead;

// Hash Queue functions
int isHashQueueEmpty(int hashQueueNumber);

void hashQueue_push_front(Buffer *ref, Buffer *buf);
void hashQueue_push_back(Buffer *ref, Buffer *buf);

void addBufferToHashQueue(Buffer *buf);
void removeBufferFromHashQueue(Buffer *buf);

Buffer *searchBlockInHashQueue(int blockNumber);
void printAllHashQueues();


// Free List functions
int isFreeListEmpty();

void freeList_push_front(Buffer *ref, Buffer *buf);
void freeList_push_back(Buffer *ref, Buffer *buf);

Buffer *removeBufferFromHeadOfFreeList();
void removeBufferFromFreeList(Buffer*);

int searchBufferInFreeList(Buffer *buffer);

// print functions
void printBuffer(int index, Buffer *p);
void printAllBuffers();
void printFreeList();

/**Buffer Cache Management Algorithms
 * 
*/
Buffer *getblk(int blk_num);    // getblock
void brelse(Buffer *buffer);    // release block

#endif // !SRC_BUFFER_CACHE_H