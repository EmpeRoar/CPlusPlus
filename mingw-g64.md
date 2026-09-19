# Install MinGW-w64 on Windows

This guide explains how to install MinGW-w64 and configure it so you can compile C++ programs from the terminal.

## 1) Download MinGW-w64

Go to the official site:

https://www.mingw-w64.org/

You can also use a common Windows package source such as:

https://github.com/brechtsanders/winlibs_mingw/releases

Choose a version that matches your system architecture:
- 64-bit: x86_64
- 32-bit: i686

For most modern machines, choose 64-bit.

## 2) Install MinGW-w64

### Option A: Use MSYS2 (recommended)
1. Download MSYS2 from:
   https://www.msys2.org/
2. Install it into a folder such as:
   - `C:\msys64`
3. Open the MSYS2 terminal.
4. Run:

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain
```

This installs the GCC compiler and related tools for 64-bit Windows.

### Option B: Install a standalone MinGW-w64 toolchain
1. Download the prebuilt MinGW-w64 package.
2. Extract it to a folder such as:
   - `C:\mingw64`
   - or `C:\msys64\mingw64`
3. Make sure the compiler folder is available in your PATH.

## 3) Add to PATH

After installation, add the compiler folder to your system PATH.

Typical folder examples:

```text
C:\msys64\mingw64\bin
C:\mingw64\bin
```

To add it in Windows:
1. Open Settings.
2. Search for Environment Variables.
3. Edit the system PATH.
4. Add the MinGW bin folder.
5. Restart your terminal.

## 4) Verify installation

Open PowerShell or Command Prompt and run:

```powershell
g++ --version
```

If it prints a version number, the compiler is installed correctly.

You can also check:

```powershell
where g++
```

## 5) Compile a C++ file

From the project folder, run:

```powershell
g++ .\hello-world\hello-world.cpp -o .\hello-world\hello-world.exe
```

Then run:

```powershell
.\hello-world\hello-world.exe
```

Expected output:

```text
Hello, World!
```

## 6) Troubleshooting

- If `g++` is not recognized, the PATH is not set correctly.
- If you installed with MSYS2, open the MSYS2 MinGW 64-bit terminal instead of the default MSYS terminal.
- If you installed a standalone build, ensure the extracted folder path is correct.
- Restart the terminal after updating PATH.

## 7) Recommended VS Code setup

Install the Microsoft C/C++ extension in VS Code, then open the project folder. This helps with IntelliSense and debugging.
