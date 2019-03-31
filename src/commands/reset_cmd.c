#include "./../bufferCache.h"
#include "./../externVariables.h"

Buffer *Clone(int blockNumber);

void reset_cmd(int argc, char *argv[]) {
  if (!initnum) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 2) {
    printf("Specify block number and status code\n");
  } else {
    int state = 0;
    for (int i = 2; i < argc; i++) {
      int num = ParseStatus(argv[i]);
      state += num;
    }
    Buffer *buffer = Clone(atoi((argv[1])));
    // int blockNumber = atoi((argv[1]));
    if (!isalpha(argv[1][0])) {
      // if(1 <= blockNumber && blockNumber <=12){
      if (buffer == NULL) {
        printf("invaid cannot get buffer\n");
      }
      // int midstate = (buffer -> status) & state;
      // buffer -> status = buffer -> status & midstate;
      buffer->status = buffer->status ^ state;

      //  else{
      // printf("Errror input value for block number should be within 1~12\n");
      //}
    } else {
      printf("This is not a number\n");
    }
  }
}