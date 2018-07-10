# Demangle

This is a tool to help you demangle C++ symbols. These are symbols that you
might see while looking at GDB backtraces, or perhaps as a result of looking at
the symbol table from `nm`, `objdump`, etc.

## Usage

Example usage:

    $ demangle _ZNSt8ios_base15sync_with_stdioEb _ZNKSt5ctypeIcE13_M_widen_initEv
    std::ios_base::sync_with_stdio(bool)  _ZNSt8ios_base15sync_with_stdioEb
    std::ctype<char>::_M_widen_init() const  _ZNKSt5ctypeIcE13_M_widen_initEv

By default the mangled symbol will be printed after the demangled symbol. If you
don't want this behavior you can use the `-q` or `--quiet` options:

    $ demangle -q _ZNSt8ios_base15sync_with_stdioEb _ZNKSt5ctypeIcE13_M_widen_initEv
    std::ios_base::sync_with_stdio(bool)
    std::ctype<char>::_M_widen_init() const

You can also get help using `demangle -h` or `demangle --help`.

## Compiling

You'll need CMake, make, and a C++ compiler. Then you should be able to do:
```
    mkdir build
    cd build
    cmake ..
    make
    sudo make install
```
If you don't want to run the `make install` step you can directly use the binary
that will be built at `src/demangle`.

**Note:** the C++ compiler you use affects which symbols you can demangle. In
particular, if you want to demangle GCC symbols you need to compile this with
GCC. Likewise, if you want to demangle Clang symbols you need to compile this
with Clang. I have intentionally avoided the use of any C++ standard library
methods to make this easy to compile on Linux to demangle OS X symbols, and
likewise to make it easy to compile on OS X to demangle Linux sysmbols.

You can figure out what "personality" the demangler was compiled with using the
`-p` or `--personality` option.

## Switching between Clang and GCC u

CMake honors the environment variables CC and CXX upon detecting the C and C++ compiler to use.
### Clang

```
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
mkdir build
cd build
cmake ..
make
sudo make install
```

Then you should see:

```
$ demangle -p
Personality: Clang/LLVM
```

### GCC

```
export CC=/usr/bin/gcc
export CXX=/usr/bin/g++
mkdir build
cd build
cmake ..
make
sudo make install
```
Then you should see:

```
$ demangle -p
Personality: GNU GCC/G++
```
