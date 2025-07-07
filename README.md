# 🐚 Egg-Shell – A Minimal Unix Shell in C++

**Egg-Shell** is a custom-built Unix shell written in C++ that mimics the core behavior of real shells like `bash` or `zsh`. It supports basic command execution, piping (`|`), and process handling using low-level Linux system calls.

---

## 🔧 Features
- ✅ Command parsing and tokenization (`ls -la`)
- ✅ Execute programs via `execvp()`
- ✅ Handle piping between two commands (`ls | grep .cpp`)
- ✅ Process management using `fork()` and `waitpid()`
- ✅ Inter-process communication via `pipe()`
- ✅ I/O redirection using `dup2()`
- ✅ Graceful error handling

## 📦 System Calls & Concepts Used
- `fork()` – create new process
- `execvp()` – execute shell commands
- `pipe()` – setup read/write communication
- `dup2()` – redirect stdin/stdout
- `waitpid()` – wait for child processes

## 🚀 How to Run

- 🛠 **Dependencies**: Linux or WSL (for system calls)
- To exit enter "slurp" (I know it sounds fun)
```bash
g++ main.cpp -o egg-shell
./egg-shell
