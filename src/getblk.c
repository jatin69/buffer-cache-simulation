#include "./bufferCache.h"

Buffer *getblk(int blk_num){

  int hash_key = blk_num % NO_OF_HASH_QUEUES;

  // @todo : can we make this infinite loop
  while (hashQueue[hash_key]->hash_next != NULL){

    // search Block in Hash Queue
    Buffer *buffer = searchBlockInHashQueue(blk_num);
    
    if (buffer != NULL){    // if buffer found in hash Queue
    
      if (isInState(buffer, BUFFER_BUSY)){    // buffer is busy : SCENARIO 5
        printf(" ********* Scenario 5 *********\n");
        printf("The kernel finds the block on the hash queue, but its buffer is currently busy.\n");
        printf("Process goes to sleep.\n");
        printf("Process will wake up when this buffer becomes free\n");
        addState(buffer, BUFFER_AWAITED);
        addToWaitingQueue(blk_num, WAITING_FOR_THIS_BUFFER);
        // sleep(); 
        // continue;
        return NULL;  // for now
      }
      else{                                   // buffer is free : SCENARIO 1
        printf("********* Scenario 1 *********\n");
        printf("The kernel finds the block on its hash queue, and its buffer is free.\n");
        setState(buffer, (BUFFER_BUSY | BUFFER_DATA_VALID));
        printf("Buffer Marked Busy.\n");
        removeBufferFromFreeList(buffer);
        printf("Removed Buffer from Free List. \n");
        return buffer;
      }
    }
    else{                  // Block is not on hash Queue
    
      if (isFreeListEmpty()){   // if there are no buffers in free list : SCENARIO 4
        
        printf("********* Scenario 4 *********\n");
        printf("The kernel cannot find the block on the hash queue, and the free list of buffers is empty.\n");
        printf("Process goes to sleep.\n");
        printf("Process will wake up when any buffer becomes free.\n");
        addToWaitingQueue(blk_num, WAITING_FOR_ANY_BUFFER);
        // sleep();
        // continue;
        return NULL;  // for now
      }

      Buffer *ref = freeListDummyHead->free_next;

      if (isInState(ref, BUFFER_MARKED_DELAYED_WRITE)){   // Buffer marked delayed write :  SCENARIO 3
        printf("********* Scenario 3 *********\n");
        printf("The kernel cannot find the block on the hash queue. Found free block is marked delayed write.\n");
        Buffer *prev = ref->free_prev;
        Buffer *next = ref->free_next;
        prev->free_next = next;
        next->free_prev = prev;
        setState(ref, BUFFER_BUSY | BUFFER_DATA_VALID | BUFFER_MARKED_DELAYED_WRITE | BUFFER_DATA_OLD);
        printf("Marking Buffer OLD. Starting Asynchronous write to disk.\n");
        continue;
      }

      // SCENARIO 2  :Found a free Buffer
      printf("********* Scenario 2 *********\n");
      printf("The kernel cannot find the block on the hash queue, so it allocates a buffer from the free list.\n");
      Buffer *freeBuffer = getBufferFromHeadOfFreeList();
      removeState(freeBuffer, BUFFER_DATA_VALID);
      printf("REMOVING FROM OLD HASH QUEUE.\nPUTTING IN NEW HASH QUEUE\n");
      freeBuffer->blockNumber = blk_num;
      addBufferToHashQueue(freeBuffer);
      printf("Kernel DISK access occuring. Status of Block Updated.\n");
      addState(freeBuffer, KERNEL_READING_WRITING);
      printf("Kernel DISK access finished. Status of Block Updated.\n");
      removeState(freeBuffer, KERNEL_READING_WRITING);
      printf("BUFFER now contains new and Valid Data. Updating status.\n");
      addState(freeBuffer, BUFFER_DATA_VALID);
      return freeBuffer;
    }
  }
  printf("BUFFER NOT FOUND\n");
  return NULL;
}
