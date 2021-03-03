# STM32 Timer Library

> An STM32-based timer / scheduler library
> This project is a STM32-based library to help organize button actions and provide a simple timer / scheduler solution.

### Main Features

- Completely written in C, making integration into HAL projects easier.
- Easy interface helps organize all timer actions in a single location.
- Robustly unit tested

### Example

```c
  Timer.init();
  Timer.every(50, Buttons.loop);
```

### Build Instructions

#### Install buildchain dependencies

```console
$ sudo apt-get install valgrind cppcheck clang-format clang ruby
```

#### Run Tests

```console
$ make clean && make test

-----------------------ANALYSIS AND TESTING SUMMARY-----------------------
0 tests ignored

0 tests failed

8 tests passed

0 memory leak(s) detected

0 code warnings

0 code errors

```
