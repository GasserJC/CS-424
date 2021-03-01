C and C++ programmers: Where I write "thread", you may substitute "process" instead.

The program must include three threads, which all run concurrently: a main thread, a producer thread, and a consumer thread. The main thread creates and starts the producer and consumer threads, then does any necessary "cleanup" work after those threads finish. The main thread may also do other things as needed.

The producer and consumer threads share a buffer. The buffer is a large array of n integers, initialized to all zeros. (Python programmers may use a Python list instead of a fixed-size array.)

The program's behavior can be adjusted by modifying 3 parameters (variables or constants).

n: the size or length of the buffer.
k: the maximum burst length, or the largest number of buffer slots that a thread can access during a single burst of activity.
t: the maximum number of seconds that each thread will sleep between bursts
The producer and consumer threads must behave as follows.

The producer executes short bursts of random duration. During each burst of length k1 (where 0 < k1 <= k), the producer adds a 1 to the next k1 slots of the buffer, modulo n.
The consumer also executes short bursts of random duration. During each burst of length k2 (where 0 < k2 <= k), the consumer reads the next k2 slots and resets each to 0.
If any slot contains a number greater than 1, then a race condition has been detected: The consumer was unable to keep up and thus the producer has added a 1 to a slot that has not yet been reset.
Both producer and consumer sleep periodically for random time intervals (between 0 and t seconds, inclusive) to emulate unpredictable execution speeds.