# CHIP-8 Emulator 🕹 

A chip-8 emulator written in C utilizing SDL3 library.

## Features 

All core features of a CHIP-8 emulator implemented in SDL3 Library.

- 35 original chip-8 instructions 
- 16-key keypad mapping to keyboard
- 64x32 monochrome display rendering
- Square wave beep sound system
- Sound and delay timers 
- ROM loading




## Building

### Dependencies

- C compiler (GCC or Clang)
- SDL3 development libraries
- GNU Make

### Build

Clone the repository and run:

```bash
make
```
### Running
```bash
./chip8 path/to/rom.ch8
```
##### Example:
```bash
./chip8 roms/Tetris.ch8
```

## Resources 🤓
These Resources were invaluable throughout my development.

- [Timendus]( https://github.com/Timendus )
Timendus is an excellent CHIP-8 resource if you ever plan on building this emulator yourself. He provides a [CHIP-8 Test Suite](https://github.com/Timendus/chip8-test-suite) repo with ROMs that test the correctness of all main features. Additionally, he has developed other projects like [Silicon8](https://github.com/Timendus/silicon8), a WebAssembly implementation of CHIP-8.

- [Tobiasvl](https://tobiasvl.github.io/)
Tobiasvl provides a full guide with implementation details and architecture information that gives an in-depth reference on how to implement the CHIP-8 emulation cycle. His [guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#logical-and-arithmetic-instructions) helps you particularly with understanding the most optimal approach for designing the 35 opcodes.
