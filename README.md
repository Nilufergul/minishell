# Minishell - A Bash Replica in C

Welcome to **Minishell**, a minimalist yet powerful replica of the Unix Bash shell, entirely written in C. This project aims to simulate the core functionalities of a Unix-like command-line interface, providing a deeper understanding of shell behavior, process management, and system calls.

## Features

Minishell supports several key functionalities:

- **Basic Command Execution**: Run common commands such as `ls`, `cat`, `echo`, etc., just like in a standard shell.
- **Built-in Commands**: Implementations for built-in commands like `cd`, `pwd`, `export`, `unset`, and `exit`.
- **Redirections and Pipes**: Input/output redirections (`>`, `<`, `>>`) and pipes (`|`) to chain commands.
- **Environment Variables**: Dynamic handling of environment variables, allowing variable expansion and management.
- **Signal Handling**: Graceful handling of `Ctrl+C`, `Ctrl+D`, and `Ctrl+\` to mimic terminal signals.
- **Command History**: Maintains a history of previously executed commands.
- **Support for Executable Files**: Run external programs, including compiled executables, directly from the shell.
- **Path Resolution**: Smart resolution of command paths for seamless execution.

## Getting Started

### Prerequisites

To run the project, you'll need a Unix-like operating system (Linux/macOS) with the following installed:

- **GCC** or another compatible C compiler
- **GNU Make**

### Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/Nilufergul/minishell
    ```

2. Navigate to the project directory:
    ```bash
    cd minishell
    ```

3. Build the project:
    ```bash
    make
    ```

4. Run the shell:
    ```bash
    ./minishell
    ```

### Usage

Once you're inside **minishell**, you can start typing commands as you would in any Unix shell. Below are a few examples:

- **Change Directory**:
    ```bash
    cd /path/to/directory
    ```

- **List Files**:
    ```bash
    ls -la
    ```

- **Redirection**:
    ```bash
    echo "Hello, Minishell!" > output.txt
    ```

- **Piping**:
    ```bash
    cat file.txt | grep "search_term"
    ```

- **Execute a Program**:
    ```bash
    ./a.out
    ```

- **Environment Variables**:
    ```bash
    export MYVAR="Hello"
    echo $MYVAR
    ```

- **Exit**:
    ```bash
    exit
    ```

### Example Session

```bash
$ ./minishell
minishell> pwd
/home/user/minishell
minishell> cd ..
minishell> echo "Learning is fun" > test.txt
minishell> cat test.txt
Learning is fun
minishell> exit
```

## Architecture

The **minishell** project is divided into multiple modules, each handling a different aspect of shell functionality:

- **Parser**: Processes the user's input, breaking it down into commands, arguments, and operators (pipes/redirections).
- **Executor**: Handles the execution of commands, whether built-in or external.
- **Environment Manager**: Manages environment variables, supporting creation, updating, and deletion.
- **Signal Handler**: Ensures that signals like `SIGINT` and `SIGQUIT` are properly captured and managed.
- **Utilities**: Helper functions for string manipulation, memory management, and system interactions.

## Limitations

While **minishell** successfully implements many core shell features, there are a few limitations:

- No job control (background processes with `&` are not supported).
- Limited error messages for certain edge cases.
- Doesn't support advanced scripting features like loops or conditionals.


