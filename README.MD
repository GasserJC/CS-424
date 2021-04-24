Write a program that implements the FIFO, LRU, and optimal page-replacement algorithms presented in section 7.2 of our zyBook.

This program does not need to be multithreaded.

User interaction with your program must follow this pattern.

    Ask the user to enter the number of page frames in the system. If the number of frames is not between 1 and 6 (inclusive), ask them to try again, and give them enough information so that they know what to do.

    Generate and then display a random reference string of length 20, whose page numbers range from 0 to 9.

    Display the number of page faults produced by using FIFO page replacement with this reference string.

    Display the number of page faults produced by using LRU page replacement with this reference string.

    Display the number of page faults produced by using optimal (OPT) page replacement with this reference string.
    
Note that this problem lends itself to a modular solution. It's best to generate the reference string in your main program (or a related method), then pass the reference string and the number of frames to separate methods for each page-replacement algorithm. Each algorithm's method should return the number of page faults required by that algorithm.

