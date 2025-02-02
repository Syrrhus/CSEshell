[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/u16ttUuk)
# CSEShell

CSEShell is a simple, custom shell for Unix-based systems, designed to provide an interface for executing system programs. This project includes a basic shell implementation, a set of system programs (`find`, `ld`, `ldr`), and some test files.

## Directory Structure

The project is organized as follows:

- `bin/` - Contains compiled executables for system programs.
  - `find` - Program to find files.
  - `ld` - Program for listing the contents of the current directory.
  - `ldr` - Program for listing the contents of the current directory recursively.
- `cseshell` - The main executable for the CSEShell.
- `files/` - Contains various test files used with the shell and system programs.
  - `combined.txt`, `file1.txt`, `file2.txt`, ... - Test text files.
  - `notes.pdf` - A PDF file for testing.
  - `ss.png` - An image file.
- `makefile` - Makefile for building the CSEShell and system programs.
- `source/` - Source code for the shell and system programs.
  - `shell.c` and `shell.h` - Source and header files for the shell.
  - `system_programs/` - Source code and header for the system programs.

## Building the Project

To build the CSEShell and system programs, run the following command in the root directory:

```bash
make
```

This will compile the source code and place the executable files in the appropriate directories.

## Running CSEShell

After building, you can start the shell by running:

```bash
./cseshell
```

From there, you can execute built-in commands and any of the included system programs (e.g., `find`, `ld`, `ldr`).

## System Programs

- `find.c` - Searches for files in a directory.
- `ld.c` - List the contents of the curent directory.
- `ldr.c` - List the contents of the current directory recursively.

Each program can be executed from the CSEShell once it is running. This starter code only allows the shell to execute a command once before exiting because `execv` replace the entire process' address space. Students need to fix this and allow the shell to prompt for more commands in Programming Assignment 1.

## Files Directory

The `files/` directory contains various text, PDF, and image files for testing the functionality of the CSEShell and its system programs.

## Makefile

The Makefile contains rules for compiling the shell and system programs. You can clean the build by running:

```bash
make clean
```

## Source Directory

Contains all the necessary source code for the shell and system programs. It is divided into the shell implementation (`shell.c`, `shell.h`) and system programs (`system_programs/`).

## Source Directory
- `cd`: Allows the user to change the current working directory of the shell

- `help`: Allows user to print out all the builtin commands in the shell

- `usage`: Print a brief description on how to use each builtin command

- `env`: Print all environment variables of this shell

- `setenv`: The command setenv KEY=VALUE simply adds to the list of this process’ environment variables

- `unsetenv`: This command unset KEY should delete any environment variable whose KEY matches any existing environmentnvariables.
  
- `exit`: quite the shell

## Additional features
- Decorate the prompt to include useful information like current path, date and time
- added a shellpet to play with while idling in shell
- -added resource usage sys program to check resource usage

## Sustainability
lightweight system programs
- we focus on making our program simple and efficient and avoid fancy graphics so that it does not take up too many resources and ensure resources are reserved for the commands
- eg. for the dcheck, we output it to temporary text file and ensured the removal to free up disk space 
- we keep all commands and programs as simple as possible and with efficient algorithms
- we included a sys program resusage to show the resource usage to evaluate the impacts of the shell on the environment for the user
  
## Inclusivity
Inclusive Error Messaging
- we have detailed error messages that are informative and user-friendly
- we wrote in simple languages as well as provided technical terms to help users understand and fix issues, using terms such as cmd, builtincommands, and even separated code for modular design for ease of reading in header files such as the code for builtindesc
  - we applied a modular structure where we split functions such that it is readable and maintainable

