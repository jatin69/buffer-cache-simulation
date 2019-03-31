#include "./../bufferCache.h"
#include "./../externVariables.h"

void free_cmd(int argc, char *argv[]) {
  if (!initnum) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  PrintFree();
}