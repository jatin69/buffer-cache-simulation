#include "./bufferCache.h"

int isStatus(Buffer *buffer, int state) { 
  return (buffer->status & state); 
}

void AddStatus(Buffer *buffer, int state) {
  buffer->status = (buffer->status) | state;
}

void MakeStatus(Buffer *buffer, int state) { 
  buffer->status = state; 
}

int CheckStatus(Buffer *buffer, int state) {
  int mask = buffer->status & state;
  return !(mask ^ state);
}

void RemStatus(Buffer *buffer, int state) { 
  buffer->status = buffer->status ^ state; 
}

void SetStatus(Buffer *h, int state) { h->status = state; }

void ResetStatus(Buffer *h, int status) { h->status = h->status ^ status; }

int ParseStatus(char *argv) {
  char val = argv[0];
  switch (val) {
  case ('L'):
    return 1;
  case ('V'):
    return 2;
  case ('D'):
    return 4;
  case ('K'):
    return 8;
  case ('W'):
    return 16;
  case ('O'):
    return 32;
  default:
    return 0;
  }
}
