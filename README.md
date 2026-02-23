*This project has been created as part of the 42 curriculum by ddamiba, mcardoso.*

---

# 🐚 minishell

## Description

**minishell** is a minimal Unix shell implemented in C, built as part of the 42 school curriculum. The goal of the project is to gain a deep understanding of how a shell works by reimplementing its core features from scratch — including command parsing, process management, I/O redirections, pipelines, environment handling, and signal management.

The shell mimics the behaviour of **bash** and supports the following features:

- **Interactive prompt** using GNU Readline (with command history)
- **Command execution** — both built-in and external commands found via `$PATH`
- **Pipelines** — chaining commands with `|`
- **Redirections** — `<`, `>`, `>>`, and `<<` (heredoc)
- **Environment variable expansion** — including `$VAR`, `$?`, and handling of quotes
- **Quote handling** — single quotes (`'`) prevent all interpretation; double quotes (`"`) allow `$` expansion
- **Signals** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave as in bash
- **Built-in commands:**
  - `echo` (with `-n` flag)
  - `cd` (relative/absolute paths, `~`, `-`)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

---

## Instructions

### Prerequisites

- GCC (or compatible C compiler)
- GNU Make
- GNU Readline development library

On Debian/Ubuntu:
```bash
sudo apt-get install libreadline-dev
```

### Compilation

Clone the repository and run `make` at the root:

```bash
git clone <repository-url> minishell
cd minishell
make
```

This will build the `libft`, `parsing`, and `execution` static libraries, then link the final `minishell` executable.

Other make targets:

| Target      | Description                                  |
|-------------|----------------------------------------------|
| `make`      | Build the project                            |
| `make clean`| Remove object files                          |
| `make fclean`| Remove object files and the executable      |
| `make re`   | Full rebuild (`fclean` + `all`)              |

### Running

```bash
./minishell
```

You will be dropped into an interactive prompt:

```
minishell$ echo "Hello, World!"
Hello, World!
minishell$ export NAME=42
minishell$ echo $NAME
42
minishell$ ls | grep ".c" | wc -l
minishell$ cat << EOF
> line one
> line two
> EOF
minishell$ exit
```

### Memory Check (optional)

A Valgrind suppression file for readline leaks is provided:

```bash
valgrind --suppressions=rlbad.supp --show-leak-kinds=all --leak-check=full --track-origins=yes --track-fds=yes ./minishell
```

---

## Resources

### Documentation & References

- **GNU Bash Manual** — The authoritative reference for bash behaviour, used throughout the project to verify how the shell should handle edge cases in parsing, expansion, quoting, and built-in commands.
  https://www.gnu.org/software/bash/manual/bash.html

- **Writing Your Own Shell** — G. Back, W. Gatliff, N. Hill, C. Norris, B. Ogles, C. Sturtivant (Purdue University) — A foundational guide covering the architecture of a Unix shell, including process creation, `exec`, pipes, and signal handling.
  https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

- **CodeVault — Unix Processes in C** (YouTube series) — A clear, practical video series covering `fork`, `exec`, `wait`, pipes, and file descriptors in C. Invaluable for understanding the execution layer of the shell.
  https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY

- **The Open Group Base Specifications (POSIX)** — Reference for system calls such as `execve`, `dup2`, `pipe`, `fork`, `waitpid`, `signal`, and `sigaction`.
  https://pubs.opengroup.org/onlinepubs/9699919799/

- **GNU Readline Library** — Documentation for the readline and history APIs used for the interactive prompt.
  https://tiswww.case.edu/php/chet/readline/rltop.html

### Use of AI

AI was used as an **information aid** throughout the project. Specific uses included:

- **Understanding bash edge cases** — Querying how bash handles specific behaviours such as `$?` expansion inside heredocs, quote stripping order relative to variable expansion, ambiguous redirections, and the exact exit codes for various error conditions.
- **Signal handling** — Clarifying the expected behaviour of signals in interactive mode vs. during command execution vs. inside heredoc input.
