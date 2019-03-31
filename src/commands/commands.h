#ifndef SRC_COMMAND_MAP_H
#define SRC_COMMAND_MAP_H

typedef struct commandFunctionMap {
  char *cmd;
  void (*func)(int, char *[]);
} commandFunctionMap;

void help_cmd   (int, char *[]);
void init_cmd   (int, char *[]);
void buf_cmd    (int, char *[]);
void hash_cmd   (int, char *[]);
void free_cmd   (int, char *[]);
void getblk_cmd (int, char *[]);
void brelse_cmd (int, char *[]);
void set_cmd    (int, char *[]);
void reset_cmd  (int, char *[]);
void quit_cmd   (int, char *[]);

commandFunctionMap commandTable[] = {
    {"help", help_cmd},     {"init", init_cmd}, {"buf", buf_cmd},
    {"hash", hash_cmd},     {"free", free_cmd}, {"getblk", getblk_cmd},
    {"brelse", brelse_cmd}, {"set", set_cmd},   {"reset", reset_cmd},
    {"quit", quit_cmd},     {NULL, NULL}};

#endif // !SRC_COMMAND_MAP_H