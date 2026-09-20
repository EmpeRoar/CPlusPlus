This devcontainer provides a Linux-based C++ development environment.

Features:
- GCC toolchain, CMake, and common debugging tools (via the base image).
- Recommended VS Code extensions: C/C++ (`ms-vscode.cpptools`), CMake Tools (`ms-vscode.cmake-tools`), CMake language support (`twxs.cmake`).

How to use:
1. Open this folder in VS Code.
2. When prompted, "Reopen in Container" or run the command: "Dev Containers: Reopen in Container".
3. Build with `g++` or `cmake` inside the container.

Example quick test:
```bash
g++ calculator/main.cpp -o calculator/app
./calculator/app
```
