# Buffer Cache Simulation

This document serves as a project writeup containing several key details regarding the project.

## Problem Statement

Buffer cache simulation. The idea was to simulate `getblk` and `brelse` algorithms 
that handle the allocation and release of buffers to processes. 
The key requirement was to be able to visualize all 5 scenarios of `getblk` and 
clearly identify the working of `getblk` in all of those scenarios.

## Suggested Solution

We want a simulation slow enough to analyse the working details of `getblk`.
Several implementations are possible. Let us glance over them.

### threads

Threads over processes because all of the children (processes) need to work on the same data structure instance (buffer cache).

Because threads can easily run into race conditions when writing to the data structure, locks need to be implemented.

Once threads and locks are in place we can think about `getblk` implementation.

We now need to show all 5 cases of `getblk` so we need to control how different threads are scheduled.
For this we need a scheduler. Either we can implement our own (which is overkill for just a simulation),
or choose the system scheduler, and forcing it to choose certain process by `sleep`ing others.

This results in an intricate mechanism of all the threads working with system scheduler. 
We have little control over the actual buffers and their status.
If we want to manipulate some buffers to test something, 
we will need to spin up another thread at runtime to handle the buffer status.

Preliminary tests show unreliability in threads and their execution order because we cannot exactly predict how the system scheduler will schedule them.

### client server architecture

Server acts as kernel, and only server manipulates the buffer cache directly.

Clients (`processes`) can ask server (`kernel`) to allocate them a buffer (`getblk`) and 
inform them when they relinquish the buffer, so kernel can release the buffer (`brelse`).

Server controls how these client requests are scheduled. 
The actual buffer cache implementation will reside with the server. 
Because, server (`kernel`) needs to be able to accept requests from multiple clients (`processses`), 
it'll spin up a new handler process for each new client.

This brings us back to our original problem. 
Now these multiple processes need to communicate and somehow share the memory region 
for manipulating buffer cache. 
Implementation complexity will be no better than the previous `threads` approach.

### User driven simulation

Let the main program act as `kernel` and manipulate the buffer cache, while user input acts as coming and going `processes`. User controls which block to get and release. User can also manipulate buffer status.

This gives us complete control over the simulation. 
Also we can view the buffer cache, freelist, buffer list, and sleeping processes at all times.

Because this will be a single-process synchronous program, there is no added complexity of managing threads. We can focus on `getblk` and `buffer cache`.

This is the chosen approach for this project.

## Programming Language Used

`C` is the chosen language. 
Because we are implementing buffer cache, which is a lower level algorithm, it needs to be fast and
`C` provides the fastest system calls. 
Also the fact that actual unix system is written in `C` made it an easy choice.

## AOS Concepts Implemented

The chosen implementation type is kept simple. So it does not use any complex constructs of AOS.

1. Forks/Threads - not required
2. Locking unlocking mechanism - not required
3. Signals - not required

## Getblk cases Handled

All 5 cases of `getblk` have been handled.

### How the request for a block is being captured

User input determines which block to `get` and `release`

### Delayed write

User manually sets a `block status` to `delayed write`.
Then when the `getblk` algorithm sees this `delayed write` marked buffer, it starts a dummy async write to disk, and moves on the next free list buffer.

## Individual Contribution & learning experience

### Jatin Rohilla

- Contributions
  - Project brainstorming
  - `brelse` algorithm and waiting queue implementation 
  - refactoring and makefile
  - test script
  
- Learning
  - read about `pthread` library and `mutex locks` for synchronization of threads
  - how to make a `makefile` for distributed project files
  - writing basic shell scripts for automated program testing

### Seema Patel

- Contribution
  - Doubly linked list for hash queues and freelist
  - getblk algorithm
  - Documentation

- Learning
  - learnt about the implementation of circular doubly linked list
  - getblk algorithm and associated scenarios