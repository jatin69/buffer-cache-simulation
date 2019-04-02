#include "./bufferCache.h"

// Add this state to buffer status
void addState(Buffer *buffer, STATE state) {
  buffer->status = (buffer->status) | state;
}

// Remove this state from buffer status
void removeState(Buffer *buffer, STATE state) { 
  buffer->status = buffer->status ^ state; 
}

// set only this state as the buffer status
void setState(Buffer *buffer, STATE state) { 
  buffer->status = state; 
}

// check if buffer is in the given state
int isInState(Buffer *buffer, STATE state) { 
  return (buffer->status & state); 
}
