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
## Practical 6 – Inter-Process Communication and Signal Handling

- Implemented **FIFO (Named Pipe) based Inter-Process Communication** using a FIFO server and client.
- Implemented **Linux signal handling** using `SIGINT`, `SIGTERM`, and `SIGUSR1`.
- Programs:
  - `fifo_server.c`
  - `fifo_client.c`
  - `signal_handler.c`

## Practical 7 – Process Memory and Address Space

- Studied the **Linux process address space** and different memory regions.
- Demonstrated **Code/Text, Data, BSS, Heap, and Stack** memory segments.
- Used `/proc/<PID>/maps` and `/proc/<PID>/status` to inspect process memory.
- Programs:
  - `memory_layout.c`
  - `memory_demo.c`

## Practical 8 – Dynamic Memory and Copy-on-Write

- Demonstrated dynamic memory management using **`malloc()`, `calloc()`, `realloc()`, and `free()`**.
- Used **Valgrind** to detect memory leaks and memory errors.
- Demonstrated **Copy-on-Write (COW)** behavior using `fork()`.
- Inspected process memory using Linux `/proc` interfaces.
- Programs:
  - `dynamic_memory.c`
  - `cow_demo.c`
## Practical 9 – File I/O and I/O Redirection

### Objective

Implement file copying using low-level Linux system calls and C standard library I/O, compare their execution time, and demonstrate input/output redirection using `dup2()`.

### Programs

#### 1. Low-Level File Copy

Program:

`Practical-9/copy_lowlevel.c`

Uses:

- `open()`
- `read()`
- `write()`
- `lseek()`
- `close()`

Compilation:

```bash
cd Practical-9
gcc -Wall -Wextra -g copy_lowlevel.c -o copy_lowlevel
