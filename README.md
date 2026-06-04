_This project has been created as part of the 42 curriculum by [masad](https://profile.intra.42.fr/users/masad), [anashwan](https://profile.intra.42.fr/users/anashwan)._

# minishell

## Description

minishell is a Unix shell implemented in C, built as part of the 42 curriculum. The goal is to recreate a minimal but functional shell that mimics core bash behavior — reading user input, parsing commands, and executing them with proper handling of pipes, redirections, environment variables, signals, and built-in commands.

The project is split across two responsibilities:

- **Parsing** — lexing input, building a command AST, handling quoting rules and variable expansion
- **Execution** — walking the AST, forking processes, setting up pipes and redirections, running builtins, and managing exit status propagation

### Features

- Command execution via `PATH` search using `fork` + `execve`
- Pipes (`|`) chaining multiple commands
- Redirections: `>`, `>>`, `<`, `<<` (heredoc with `$VAR` / `$?` expansion)
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable expansion (`$VAR`, `$?`)
- Signal handling: `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- Readline-based interactive prompt with in-session history

---

## Instructions

### Compilation

```bash
make
```

Produces the `minishell` executable in the project root.

```bash
make clean    # remove object files
make fclean   # remove object files + binary
make re       # fclean then rebuild
```

### Execution

```bash
./minishell
```

Launches an interactive prompt. Exit with `exit` or `Ctrl+D`.

```bash
# Example commands
echo "hello world"
ls -la | grep .c
cat < input.txt > output.txt
export NAME=minishell
echo $NAME
```

---

## Resources

### Documentation & references

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — authoritative reference for shell behavior, builtins, and expansions
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — documentation for the readline API used for the interactive prompt
- [POSIX Shell Specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — standard reference for POSIX-compliant shell behavior
- [Writing Your Own Shell — Purdue CS](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf) — tutorial walkthrough of shell internals
- [how to use the dup2 System Call](https://www.youtube.com/watch?v=PIb2aShU_H4) — A C tutorial for redirecting stdin and stdout using system calls
- `man 2 fork`, `man 3 execve`, `man 2 pipe`, `man 2 dup2`, `man 3 readline` — essential system call and library references

### AI usage

Claude (Anthropic) was used during this project for the following:

- **Debugging** — diagnosing a bug in command iteration that caused incorrect execution when chaining builtins and external commands in the same pipeline
- **Design questions** — discussing trade-offs in AST node structure and how to propagate exit status through pipes

AI was not used to write or generate source code.

---

## Authors

- [Montaser Asad](https://github.com/montaser-asad)

- [Ahmad Nashwan](https://github.com/ahmad-nashwan)
