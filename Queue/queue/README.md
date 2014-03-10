# Multithreaded Test

This is my testbed for multithreaded classes. I've written a MessageQueue class
that uses locking already. I use pthreads for everything, as any respectable
unix programmer would. To see some examples for my method of writing C code that
has object orientation, see
[object-oriented-test](https://github.com/coderarity/object-oriented-test).

Examples are provided in main.c. I may expand this testbed as I add more classes
for multithreaded communications.

## Build it

```
make
```

## Try it

```
./test
```

## Clean it

```
make clean
```

## Check it for memory leaks (requires valgrind)

```
make memcheck
```

# License

All code and documentation in this repository is released under the MIT license.
See [license text](http://coderarity.mit-license.org/).

