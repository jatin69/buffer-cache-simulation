#include "./../bufferCache.h"
#include "./../externVariables.h"

int parseStatus(char *argv);

void set_cmd(int argc, char *argv[]) {
  if (!bufferHasBeenInitialised) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 2) {
    printf("Specify block number and status code\n");
  } else {
    int state = 0;
    for (int i = 2; i < argc; i++) {
      int num = parseStatus(argv[i]);
      state += num;
    }
    Buffer *buffer = searchBlockInHashQueue(atoi((argv[1])));
    int blockNumber = atoi((argv[1]));
    if (!isalpha(blockNumber)) {
      if (1 <= blockNumber && blockNumber <= 12) {
        if (buffer == NULL) {
          printf("invaid cannot get buffer\n");
        }
        buffer->status = buffer->status | state;
      } else {
        printf("Errror input value for block number should be within 1~12\n");
      }
    } else {
      printf("This is not a number\n");
    }
  }
}
