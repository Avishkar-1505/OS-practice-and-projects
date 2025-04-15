# Chapter 3 Programming Problems

1. **Creating Zombie:**

    C program that forks
    a child process that ultimately becomes a zombie process. This zombie
    process must remain in the system for at least 10 seconds.

2. **Timing Commands (Use of IPC)**

    Write a C program called time.c that determines the amount of time
    necessary to run a command from the command line. This program will
    be run as "./time command" and will report the amount of elapsed
    time to run the specified command.

    **ver1** Using shared memory region

    **ver2** Using Pipe

    **Example Output:**

    ```
    ./time ls
    time.c
    time

    Elapsed time: 0.25422
    ```

3. **Simulating Operating System’s pid manager**

    Use the following constants to identify the range of possible pid
    values:

    ```
    #define MIN PID 300
    #define MAX PID 5000
    ``` 
    You may use any data structure of your choice to represent the availability of process identifiers. One strategy is to adopt what Linux has done and use a bitmap in which a value of 0 at position i indicates that
    a process id of value i is available and a value of 1 indicates that the process id is currently in use.

    Implement the following API for obtaining and releasing a pid:
    - int allocate map(void) —> Creates and initializes a data structure for representing pids; returns −1 if unsuccessful, 1 if successful
    - int allocate pid(void) —> Allocates and returns a pid; returns
    −1 if unable to allocate a pid (all pids are in use)
    - void release pid(int pid) —> Releases a pid
    
4. **Collatz conjecture**

    The Collatz conjecture concerns what happens when we take any positive integer n and apply the following algorithm:

    ```
    n = n∕2, if n is even
    n = 3 × n + 1, if n is odd
    ```
    The conjecture states that when this algorithm is continually applied,
    all positive integers will eventually reach 1. For example, if n = 35
    ```
    n = 35 the sequence is
    35, 106, 53, 160, 80, 40, 20, 10, 5, 16, 8, 4, 2, 1
    ```
    Write a C program using the fork() system call that generates this
        sequence in the child process. The starting number will be provided from the command line. Because the
    parent and child processes have their own copies of the data, it will be
    necessary for the child to output the sequence. Have the parent invoke
    the wait() call to wait for the child process to complete before exiting
    the program. Perform necessary error checking to ensure that a positive
    integer is passed on the command line.

5. **Collatz conjecture using shared memory**

    In the previous problem, the child process must output the sequence of numbers generated from the algorithm specified by the Collatz conjecture
    because the parent and child have their own copies of the data. Another
    approach to designing this program is to establish a shared-memory
    object between the parent and child processes. This technique allows
    the child to write the contents of the sequence to the shared-memory
    object. The parent can then output the sequence when the child completes. Because the memory is shared, any changes the child makes will
    be reflected in the parent process as well.
    This program will be structured using POSIX shared memory. The parent process will progress through the
    following steps:
    - Establish the shared-memory object (shm open(), ftruncate(),
    and mmap()).

    - Create the child process and wait for it to terminate.

    - Output the contents of shared memory.

    - Remove the shared-memory object.

6. **Socket Program**

    Write simple program using socket connection to create a server that delivers quote of the day when a client connects The quotes should be printable ASCII characters and should contain fewer than 512 characters, although multiple lines are allowed. Have your server listen to port 6017.

7. **Haiku Socket Program**

    Write simple program using socket connection to create a server that delivers a haiku when a client connect. Have your server listen to port 5575.

8. **Echo Server**

    Write an echo server using the Java networking API This server will wait for a client connection using the accept() method. When a client connection is received, the server will loop, performing the following steps:
    - Read data from the socket into a buffer.
    - Write the contents of the buffer back to the client.

    The server will break out of the loop only when it has determined that
    the client has closed the connection.

9. **Reverse Case Using Pipe**

    Design a program using ordinary pipes in which one process sends a string message to a second process, and the second process reverses
    the case of each character in the message and sends it back to the first
    process. For example, if the first process sends the message Hi There,
    the second process will return hI tHERE. This will require using two
    pipes, one for sending the original message from the first to the second
    process and the other for sending the modified message from the second
    to the first process. You can write this program using either UNIX or
    Windows pipes.

