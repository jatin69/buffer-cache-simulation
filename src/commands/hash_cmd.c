#include "./../bufferCache.h"
#include "./../externVariables.h"

void hash_cmd(int argc, char *argv[]) {
  if (!initnum) {
    printf("Error! Nothing is started\n");
    printf("You should call init first\n");
    return;
  }
  if (argc <= 1) {
    PrintHashAll();
  } else {
    for (int i = 1; i < argc; i++) {
      if (!isalpha((argv[i][0]))) {
        if (0 <= atoi(argv[i]) && atoi(argv[i]) <= 3) {
          PrintHashLine(atoi(argv[i]));
        } else {
          printf("INPUT VALUE MUST BE WITHIN 0 ~ 3\n");
        }
      } else {
        printf("Please specify a natural number\n");
      }
    }
  }
}
