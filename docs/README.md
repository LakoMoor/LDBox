# **LDBox**

# Building the LDBox

## Windows

*   MinGW-w64 (https://sourceforge.net/projects/mingw-w64/)
*   Git (https://git-scm.com/)
*   CMake 3.20.5 minimum: [https://cmake.org/download/](https://cmake.org/download/)

## Linux

```shell
sudo apt install git cmake build-essential clang -y
```

#

#### Clone the repository 
```shell
git clone https://github.com/LakoMoor/LDBox.git
```
#### Quick start engine setup
```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

`README will be update!`