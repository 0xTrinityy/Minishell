# Minishell

Minishell is a minimalistic Unix-like shell implementation written in C. It provides a basic command-line interface and supports executing various shell commands and features, making it a lightweight alternative to traditional Unix shells. Made by Lucienfer and Tbelleng

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Examples](#examples)

## Features
- Implements a simple and functional command-line interface.
- Supports common shell features, such as command execution, path resolution, and environment variable handling.
- Provides a user-friendly prompt for entering commands.
- Supports basic shell scripting with redirection and pipes.

## Prerequisites
Before you begin, ensure you have met the following requirements:
- You should have a C compiler (e.g., GCC) installed on your system.

## Installation
Clone the repository and ```make```, its will build ./minishell binary.

## Examples

# Execute a simple command
$ ls -l

# Use pipes to pass the output of one command to another
$ ls -l | grep keyword

# Redirect input and output
$ cat file.txt > newfile.txt

