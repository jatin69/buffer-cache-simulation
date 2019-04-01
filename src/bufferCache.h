#ifndef SRC_BUFFER_CACHE_H
#define SRC_BUFFER_CACHE_H

// standard headers
#include <stdio.h>
#include <stdlib.h>
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

// Is it locked(BUSY) or FREE
#define STAT_LOCKED 0x00000001
// Does it contain valid data 
#define STAT_VALID 0x00000002
// Is the buffer marked delayed write
#define STAT_DWR 0x00000004
// Is kernel currently reading/writing this buffer to memory
#define STAT_KRDWR 0x00000008
// Is another process waiting for this buffer
#define STAT_WAITED 0x00000010
// Is buffer marked old
#define STAT_OLD 0x00000020 

// status Manipulation
int isStatus(Buffer *buffer, int state);
void AddStatus(Buffer *buffer, int state);
int CheckStatus(Buffer *buffer, int state);
void RemStatus(Buffer *buffer, int state);
void MakeStatus(Buffer *buffer, int state);
void SetStatus(Buffer *h, int status);
void ResetStatus(Buffer *h, int status);
int ParseStatus(char *argv);


/**Doubly Linked List Management
 * 
*/
#define NO_OF_HASH_QUEUES 4
// Buffer hashQueue[NO_OF_HASH_QUEUES];
// Buffer freeListDummyHead;

Buffer** hashQueue;
Buffer* freeListDummyHead;

// Hash Queue functions
void hashQueue_push_front(Buffer *h, Buffer *p);
void hashQueue_push_back(Buffer *h, Buffer *p);
Buffer *remove_hash_head();
void remove_hash(Buffer *p);
int isHashQueueEmpty(int hashQueueNumber);
Buffer *searchBufferInHashQueue(int blockNumber);
void addToHashQueue(Buffer *elem);


// Free List functions
void freeList_push_front(Buffer *h, Buffer *p);
void freeList_push_back(Buffer *h, Buffer *p);
Buffer *remove_free_head();
void removeBufferFromFreeList(Buffer*);
int isInFreeList(Buffer *buffer);
Buffer *getfreeListDummyHead();
int isFreeListEmpty();

// pretty printing Functions
void PrintState(Buffer *p);
void PrintBufferOne(int index);
void PrintBufferAll();
void PrintHashLine(int hkey);
void PrintHashAll();
void PrintFree();
void PrintRoutine(Buffer *p, int index);
int SearchNum(int blockNumber);


/**Buffer Cache Management Algorithms
 * 
*/
Buffer *getblk(int blk_num);    // getblock
void brelse(Buffer *buffer);    // release block


#endif // !SRC_BUFFER_CACHE_H