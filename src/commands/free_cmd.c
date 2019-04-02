#include "./../bufferCache.h"

/**Command Handler : free
 * 
 * Displays free list
*/
void free_cmd(int argc, char *argv[]) {
  printFreeList();
}