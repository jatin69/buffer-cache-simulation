#include "./bufferCache.h"

// check if waiting queue is empty
int isWaitingQueueEmpty() {
    for(int i=0; i<SIZE_OF_WAITING_QUEUE; ++i){
        if(waitingQueue[i] != 0){
            return 0;
        }
    }
    return 1;
}

// add process asking `blk_num` to waiting queue
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

    // randomly choose which type of process will win the race condition
    srand(time(NULL));
    if(rand()%2 == 0){  winner = WAITING_FOR_ANY_BUFFER;  }
    else             {  winner = WAITING_FOR_THIS_BUFFER; }

    // choose a process from the winner category
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

    // if no process exists in the winner category
    if(returnValue == 0){
        
        // make the other category winner 
        if(winner == WAITING_FOR_ANY_BUFFER){
            winner = WAITING_FOR_THIS_BUFFER;
        }
        else if(winner == WAITING_FOR_THIS_BUFFER){
            winner = WAITING_FOR_ANY_BUFFER;
        }

        // choose a process from the winner category
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

    // print winner and its required block number 
    if(winner == WAITING_FOR_ANY_BUFFER) {
        printf("Race Winner is a process WAITING_FOR_ANY_BUFFER ");
    }
    else if( winner == WAITING_FOR_THIS_BUFFER){
        printf("Race Winner is a process WAITING_FOR_THIS_BUFFER ");
    }
    printf("and it wants block number %d.\n", returnValue);
    return returnValue;
}


