#include "./bufferCache.h"

Buffer *getblk(int blk_num)
{
  int hash_key = blk_num % 4;
  while (&hashQueue[hash_key] != NULL)
  {
    Buffer *buffer = searchBufferInHashQueue(blk_num);
    if (buffer != NULL)
    {
      assert(buffer != NULL);
      if (isStatus(buffer, STAT_LOCKED))
      {
        // sleep();
        printf("=== Scenario 5 ===\n");
        printf("The kernel finds the block on the hash queue, but its buffer is currently busy.\n");
        printf("Process goes to sleep\n");
        AddStatus(buffer, STAT_WAITED);
        return NULL;
        continue;
      }
      printf("=== Scenario 1===\n");
      printf("The kernel finds the block on its hash queue, and its buffer is free.\n");
      MakeStatus(buffer, (STAT_LOCKED | STAT_VALID));
      printf("Buffer Allocated.\n");
      removeBufferFromFreeList(buffer);
      printf("Removed Buffer from Free List. \n");
      return buffer;
    }
    else
    {
      if (isFreeListEmpty())
      {
        // sleep();
        printf("=== Scenario 4===\n");
        printf("The kernel cannot find the block on the hash queue, and the free list of buffers is empty.\n");
        printf("Process goes to sleep\n");
        printf("Will Wake Up when some buffer gets free, and it receives a signal of that.\n");
        // @todo : release an appropriate buffer
        // brelse(buffer);
        // continue;
        return NULL;  // for now
      }

      Buffer *ref = getFreeListHead();
      if (CheckStatus(ref, STAT_DWR))
      {
        // scenario 3
        printf("=== Scenario 3===\n");
        printf("The kernel cannot find the block on the hash queue. Found free block is marked delayed write.\n");
        Buffer *prev = ref->free_prev;
        Buffer *next = ref->free_next;
        prev->free_next = next;
        next->free_prev = prev;
        MakeStatus(ref, STAT_LOCKED | STAT_VALID | STAT_DWR | STAT_OLD);
        printf("Marking Buffer OLD. Starting Asynchronous write to disk.\n");
        continue;
      }
      // scenario 2
      printf("=== Scenario 2===\n");
      printf("The kernel cannot find the block on the hash queue, so it allocates a buffer from the free list.\n");
      Buffer *additionalbuf = remove_free_head();
      RemStatus(additionalbuf, STAT_VALID);
      additionalbuf->blockNumber = blk_num;
      addToHashQueue(additionalbuf);
      printf("Kernel HDD access occuring. Status of Block Updated.\n");
      AddStatus(additionalbuf, STAT_KRDWR);
      printf("Kernel HDD access finished. Status of Block Updated.\n");
      RemStatus(additionalbuf, STAT_KRDWR);
      AddStatus(additionalbuf, STAT_VALID);
      return additionalbuf;
    }
  }
  printf("BUFFER NOT FOUND\n");
  return NULL;
}
