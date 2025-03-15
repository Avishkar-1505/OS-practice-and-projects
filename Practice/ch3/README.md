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



