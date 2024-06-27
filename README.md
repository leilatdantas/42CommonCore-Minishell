# Minishell

## Table of Contents
- [Project Overview](#project-overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Error Handling](#error-handling)
- [Testing](#testing)
- [Contributors](#contributors)
- [License](#license)

## Project Overview
Minishell is a simple, UNIX command interpreter built as part of the 42 School curriculum. It provides a basic shell environment for executing commands, managing processes, and handling input/output redirections.

## Features
- Basic command execution
- Built-in commands (`cd`, `echo`, `env`, `pwd`, `unset`, `exit`, `export`)
- Input and output redirection
- Pipe handling (`|`)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Environment variable management

## Installation
To install and run Minishell, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/minishell.git
   ```
2. **Navigate to the project directory:**
   ```bash
   cd minishell
   ```
3. **Build the project:**
   ```bash
   make
   ```
## Usage
After building the project, you can start the shell by running:
   
   ```bash
   ./minishell
   ```
Once inside the shell, you can type commands just like you would in a regular UNIX shell. For example:
   ```bash
   MINISHELL ls -l
minishell$ cd /path/to/directory
minishell$ echo "Hello, world!"
minishell$ cat file.txt | grep "pattern"

Built-in Commands

Minishell supports the following built-in commands:

    cd [directory]: Change the current directory.
    echo [string ...]: Display a line of text.
    env: Display the environment variables.
    setenv [key] [value]: Set an environment variable.
    unsetenv [key]: Remove an environment variable.
    exit [status]: Exit the shell with a status code.

Error Handling

Minishell includes basic error handling to manage:

    Command not found errors
    Permission denied errors
    Syntax errors in input
    Invalid arguments for built-in commands

Testing

To test the Minishell, you can use various command-line inputs and verify the outputs. Automated tests and scripts can also be used to ensure the shell behaves as expected.
