# Project Overview
This project simulates a multi-phase car racing scenario using pthreads in C. Each phase introduces different concurrency concepts, 
including basic thread creation, mutex synchronization, deadlock scenarios, and deadlock prevention techniques.

# Build and Run Instructions

## Building the Project
Ensure you have `gcc` installed. Compile each phase using:
```sh
gcc -o phase1 Phase1.c -pthread
gcc -o phase2 Phase2.c -pthread
gcc -o phase3 Phase3.c -pthread
gcc -o phase4 Phase4.c -pthread
```

## Running the Executables
Execute each phase as follows:
```sh
./phase1
./phase2
./phase3
./phase4
```

# IPC Solution
For inter-process communication (IPC) solution mentioned in the project:
- Run the necessary commands in Linux to execute the required IPC functionalities.
- Ensure the correct permissions and synchronization mechanisms are in place for successful IPC operations.

# Notes
- Each phase progressively introduces new concurrency challenges.
- The final phase demonstrates deadlock prevention and timeout mechanisms.
- Run each executable separately to observe different behaviors at each phase.
