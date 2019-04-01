#include "./bufferCache.h"

void addState(Buffer *buffer, STATE state) {
  buffer->status = (buffer->status) | state;
}

void removeState(Buffer *buffer, STATE state) { 
  buffer->status = buffer->status ^ state; 
}

void setState(Buffer *buffer, STATE state) { 
  buffer->status = state; 
}

int isInState(Buffer *buffer, STATE state) { 
  return (buffer->status & state); 
}
