#include "./../bufferCache.h"
#include "./../externVariables.h"

void buf_cmd(int argc, char *argv[]) {
  if (!initnum) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 1) {
    PrintBufferAll();
  } else {
    for (int i = 1; i < argc; i++) {
      char array[100];
      strncpy(array, argv[i], 100);
      if (!isalpha((array[0]))) {
        if (0 <= atoi(array) && atoi(array) <= 11) {
          PrintBufferOne(atoi(array));
          printf("\n");
        } else {
          printf("buffer number must be within 0 ~ 11\n");
        }
      } else {
        printf("Block number should be a natural number\n");
      }
    }
  }
}
