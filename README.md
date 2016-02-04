# Demangle

This is a tool to help you demangle C++ symbols. These are symbols that you
might see while looking at GDB backtraces, or perhaps as a result of looking at
the symbol table from `nm`, `objdump`, etc.

## Usage

Example usage:

    $ demangle _ZNSt8ios_base15sync_with_stdioEb _ZNKSt5ctypeIcE13_M_widen_initEv
    std::ios_base::sync_with_stdio(bool)  _ZNSt8ios_base15sync_with_stdioEb
    std::ctype<char>::_M_widen_init() const  _ZNKSt5ctypeIcE13_M_widen_initEv

You can also get help using `demangle -h` or `demangle --help`.

## Compiling

You'll need autotools, make, and a C++ compiler. Then you should be able to do:

    ./autogen.sh
    ./configure
    make
    make install

If you don't want to run the `make install` step you can directly use the binary
that will be built at `src/demangle`.

**Note:** the C++ compiler you use affects which symbols you can demangle. In
particular, if you want to demangle GCC symbols you need to compile this with
GCC. Likewise, if you want to demangle Clang symbols you need to compile this
with Clang.

### Clang on Linux

I have intentionally avoided the use of any C++ standard library methods to make
this easy to compile on Linux systems that normally use GCC's libstdc++. If
you're on a Linux system like Debian, Ubuntu, Fedora, or likely any other
distribution that normally uses GCC and you want to build this with Clang to
demangle Clang symbols you can compile it like this:

    CXX=clang++ ./configure
    make

### GCC on OS X

The same applies for OS X, which normally uses Clang. If you want to demangle
GCC symbols you'd do:

    CXX=g++ ./configure
    make
