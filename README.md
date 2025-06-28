# 🐚 Minishell

**Minishell** is a simplified UNIX shell implemented in C.
It reproduces key behaviors of bash, including command parsing, execution, redirections, and piping.

> 👥 This project was developed collaboratively with misaac-c

---

## ⚙️ Features

- Prompt display and input reading
- Built-in commands:
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Environment variable handling (`$VAR`)
- Command execution (with absolute or relative paths)
- Redirections: `>`, `>>`, `<`, `<<` (heredoc)
- Pipes: `|` (including multi-piping)
- Signal handling (Ctrl+C, Ctrl+\)
- Proper memory management and leak-free execution

---

## 🧪 Example

```bash
$ echo Hello | cat -e > file.txt
$ cat file.txt
Hello$
