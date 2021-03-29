General Instructions
Write a multithreaded implementation of the Banker's algorithm. In this implementation, you will create a model of a multiprocessing computer system where several processes are requesting and releasing random amounts of resources at random times.

Command-line arguments
Your program should accept two command-line arguments.

One of two words: manual if your program will run in manual mode, or auto if your program will run in automatic mode.
The path to a "setup file", a text file that describes the initial setup for the system that you will simulate. Your program will use this file to initialize its data structures.
If you write your program in Java, if your main class is named BankerAlg, and if your input file is named test2.txt and is in the directory where you are issuing the Java command, then your command to run the Java program might look like

java BankerAlg manual test2.txt
If you write your program in C or C++, and if your input file is named test2.txt and is in the same directory as your compiled program file, then you might run your program with a command like

./a.out manual test2.txt
 

Setup file
The structure of your setup file should be similar to the following example. The specific numbers can be different, but the structure should be the same.

3 resources
5 processes
Available
6 7 12
Max
4 5 6
3 1 2
1 2 2
0 3 1
5 4 7
Allocation
0 0 0
0 0 0
0 0 0
0 0 0
0 0 0
Your program should use this input file to set the numbers of resources and processes (customers), then initialize the Available, Max, and Allocation arrays. (See the Banker's Algorithm data structures page for more information about these arrays.)

This makes it easier for you to run your code with different test cases. Visit the Test Cases for Program 3 page to get input files and commands for two pre-made test cases. When I grade your program, I will try running it with these two test cases, plus some additional test cases that I will write.

 

Check initial conditions
Before continuing to the next part, your program should perform checks to ensure that all of the following conditions are true at the start for every process Pi and every resource type Rj.

Allocation[Pi][Rj]≤Maximum[Pi][Rj]
(∑iAllocation[Pi][Rj])+Available[Rj]=Total[Rj]
(in English: You can't allocate more resources of a given type than actually exist.)
The system is in a safe state.
If any of these conditions are false, the program should display an appropriate error message and then exit.

If all of these conditions are true, then the program should continue to the next step.

 

Choose a mode: manual or automatic
Your program should be able to run in two different modes: manual mode if manual is given on the command line, or automatic mode if auto is given on the command line.

 

Manual mode
In manual mode, your program should allow the user to enter any of the following three types of commands.

request I of J for K
release I of J for K
end
A request or release command word should be followed on the same line by

number of elements being requested (requests between 0 and Max[K][J], releases between 0 and Allocation[K][J]), then
the word of followed by the resource type ID being requested (between 0 and m-1), then
the word for followed by the process ID making the request (between 0 and n-1).
For example, request 3 of 1 for 0 requests 3 units of resource R_1 for process p_0.

An end command word exits the program.

 

Automatic mode
In automatic mode, your program will apply the Banker's algorithm to a simulation of a multiprocess system. Your program must create one thread for each of the n processes ("customers") in the system that you are simulating.

Each thread must randomly generate 3 request commands and 3 release commands for itself. (You may hard-code these numbers.) Within each thread, requests should alternate with releases. When each thread completes its 3 requests and 3 releases, it should terminate. The program ends after all threads terminate.

Note that processes should not release all of their resources immediately after a request for more resources is granted. Both requests and releases should be randomly generated.

The threads should be able to run in parallel if your system allows it. All threads will share the same set of arrays, so you will need to control access to the arrays using mutex locks, semaphores, or similar structures in order to ensure data integrity.

 

Handling requests
Each request must be checked using the Banker's algorithm before it is granted.

A request must be granted if and only if the Banker's algorithm shows that the system will still be in a safe state after the request is granted.

If the request will put the system into an unsafe state, then do the following steps.

Deny the request.
Reverse any changes that were made to the arrays during the Banker's algorithm (unless the program worked on copies of the arrays).
Allow the requesting thread to continue. You do not need to make the requesting thread wait for enough resources to become available.
 

Handling releases
If the number of units to be released is valid (non-negative and not more than the process holds), then release the resources.

Otherwise, display an error message and do not change the arrays.

 

Required output
Your program must display the following output, to help you debug your program and to help me grade it. This output should be displayed in both manual mode and automatic mode.

For each request, (a) the process/thread number, (b) the type and number of requested resource units, and (c) whether the request was granted or denied.
Example: "Process 2 requests 3 of resource 1: denied"
For each release, (a) the process/thread number and (b) the type and number of released resource units.
Example: "Process 1 releases 4 of resource 2"
You may also want to display the initial state of the system (i.e., contents of "maximum" and "available" arrays at start) to help you debug your program. However, this is not required.