# OS Practicals

## Practical 1
Implementation of Operating Systems Practical 1.

## Practical 2
Implementation of Operating Systems Practical 2.

## Practical 3

Implementation of process creation and process management using `fork()`.

The program demonstrates:

- Parent and Child process creation
- Process ID (PID)
- Parent Process ID (PPID)
- Process states
- `fork()` system call
- `wait()` system call
- Process synchronization
## Practical 4 – Process Synchronization using wait() and waitpid()

### Objective

Write a C program where a parent process creates multiple child processes and synchronizes their completion using `wait()` and `waitpid()`.

### Concepts Covered

- Parent and child processes
- `fork()`
- `wait()`
- `waitpid()`
- Process synchronization
- Child process termination
- Exit status using `WIFEXITED()` and `WEXITSTATUS()`

### Program

The program is available in:

`Practical-4/wait_waitpid_demo.c`

### Compilation

```bash
gcc wait_waitpid_demo.c -o wait_waitpid_demo
```

## Practical 5 – Inter-Process Communication Using Pipes

### Program 1: Producer-Consumer Communication Using Anonymous Pipe

#### Objective

Implement a producer-consumer communication system using an anonymous pipe, where the parent process acts as the producer and the child process acts as the consumer.

#### Concepts Covered

- `pipe()`
- `fork()`
- `read()`
- `write()`
- Anonymous pipe
- Parent-child process communication
- `wait()`
- Communication time measurement
- Throughput calculation
- `clock_gettime()`

#### Program

`Practical-5/prog5.c`

#### Compilation

```bash
gcc prog5.c -o prog5
```
