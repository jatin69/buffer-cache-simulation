# Buffer Cache

A simple buffer cache implementation for simulation of `getblk` and `brelse` algorithms.

## Overview

In this implementation, the main program act as `kernel` and manipulates the buffer cache, while user input acts as coming and going `processes`. User controls which block to get and release. User can also manipulate buffer status. This gives us complete control over the simulation.  Also we can view the buffer cache, freelist, buffer list, and sleeping processes at all times.

This is a single-process synchronous program, so there is no added complexity of managing threads. 
<br>Read the [project writeup](./writeup.md) to know more about the current implementation.

For a multi-threaded implementation, visit [this repository](https://github.com/jatin69/multithreaded-buffer-cache-simulation).


## How to Run

- Compile using `make`
- Then you can simply run the executable `./bufcache`
- Alternatively, use `make run` 

## How to test

- Run tests and see scenarios by executing test script `./test.sh`
- Alternatively, use `make test`
- In the logs folder, you can find the [testlogs](./logs/testlog.txt).

## Demo

Checkout the [logs folder](./logs/) for demo program runs.

## Supported Commands

Directly from the help section of the program.

```
help


buf 
	Display the status of all the buffers.
hash
	Display all the Hash Queues.
free
	Display free list
wait
	Display waiting Queue
exit
	To exit the simulation

getblk <blockNumber>

	Take the blockNumber from the user, execute getblk(n)

brelse <blockNumber>

	Take the blockNumber from the user, execute brelse() 

set <blockNumber> <statusCode> 

	Set the status of the buffer to status code

	B : Buffer Busy
	V : Buffer Data is Valid
	D : Buffer is marked delayed write
	K : Kernet is reading/writing buffer to disk
	W : Buffer is awaited by some other process
	O : Buffer Data is OLD

reset <blockNumber> <statusCode> 

	Reset the status of the buffer to status code

	B : Buffer Busy
	V : Buffer Data is Valid
	D : Buffer is marked delayed write
	K : Kernet is reading/writing buffer to disk
	W : Buffer is awaited by some other process
	O : Buffer Data is OLD

```