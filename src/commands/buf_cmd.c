#include "./../bufferCache.h"
#include "./../externVariables.h"

void buf_cmd(int argc, char *argv[]) {
  if (!bufferHasBeenInitialised) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  printAllBuffers();
}
