# Buffer Cache

A simple buffer cache implementation for simulation of `getblk` and `brelse` algorithms.

Find the project writeup [here](./writeup.md) containing several key decisions of the project.

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