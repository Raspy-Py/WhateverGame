## Prerequisites

- Any C++ compiler: g++ | MSVC | Clang
- CMake

### Linux specific
Project uses SFML library which has a bunch of dependencies by itself. To install them on Ubuntu use the following command:


```bash
xargs -a requirements-linux.txt sudo apt-get install
```


## Compilation

To compile for Linux run the following command in the project root:
```bash
./CompileLinux.sh -O
```

For Windows:
```bash
CompileWindows.bat -O
```

[*] - Remove "-O" for debug build.

## Installation

Project uses git submodules, so to install it run the following command:
```bash
git clone --recurse-submodules https://github.com/Raspy-Py/WhateverGame.git
```
