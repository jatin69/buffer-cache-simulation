#include "./bufferCache.h"

int isWaitingQueueEmpty() {
    for(int i=0; i<SIZE_OF_WAITING_QUEUE; ++i){
        if(waitingQueue[i] != 0){
            return 0;
        }
    }
    return 1;
}

void addToWaitingQueue(int blk_num, WAITING_TYPE waitType) {
    int len;
    for(len=0; waitingQueue[len]!=0 && len < SIZE_OF_WAITING_QUEUE ;++len);

    if(len == SIZE_OF_WAITING_QUEUE) { 
        printf("TOO MANY WAITING PROCESSES. KILLING LEAST RECENTLY USED ONE.");
        len = 0;
    }
    waitingQueue[len] = blk_num * waitType;
}

int getProcessFromWaitingQueue(int blockNumber) {

    WAITING_TYPE winner ;

    srand(time(NULL));
    if(rand()%2 == 0){  winner = WAITING_FOR_ANY_BUFFER;  }
    else             {  winner = WAITING_FOR_THIS_BUFFER; }

    int returnValue = 0;
    for(int i=0; i<SIZE_OF_WAITING_QUEUE; ++i){
        if(winner == WAITING_FOR_ANY_BUFFER && waitingQueue[i] > 0){
            returnValue = waitingQueue[i];
            waitingQueue[i] = 0;
            break;
        }
        if(winner == WAITING_FOR_THIS_BUFFER && waitingQueue[i] < 0 && blockNumber == waitingQueue[i]*-1){
            returnValue = waitingQueue[i] * -1;
            waitingQueue[i] = 0;
            break;
        }
    }

    if(returnValue == 0){
        if(winner == WAITING_FOR_ANY_BUFFER){
            winner = WAITING_FOR_THIS_BUFFER;
        }
        else if(winner = WAITING_FOR_THIS_BUFFER){
            winner = WAITING_FOR_ANY_BUFFER;
        }
        for(int i=0; i<SIZE_OF_WAITING_QUEUE; ++i){
            if(winner == WAITING_FOR_ANY_BUFFER && waitingQueue[i] > 0){
                returnValue = waitingQueue[i];
                waitingQueue[i] = 0;
                break;
            }
            if(winner == WAITING_FOR_THIS_BUFFER && waitingQueue[i] < 0 && blockNumber == waitingQueue[i]*-1){
                returnValue = waitingQueue[i] * -1;
                waitingQueue[i] = 0;
                break;
            }
        }
    }

    if(winner == WAITING_FOR_ANY_BUFFER) {
        printf("Race Winner is a process WAITING_FOR_ANY_BUFFER ");
    }
    else if( winner == WAITING_FOR_THIS_BUFFER){
        printf("Race Winner is a process WAITING_FOR_THIS_BUFFER ");
    }
    printf("and it wants block number %d.\n", returnValue);
    return returnValue;
}


