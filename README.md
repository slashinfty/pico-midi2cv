# MIDI to CV converter

Altered from [https://www.peterzimon.com/cv-keyboard/](https://www.peterzimon.com/cv-keyboard/)

## About
A simple MIDI to CV converter using MCP4288 DAC.

## Dependecies
Uses [`pico-lib`](https://github.com/peterzimon/pico-lib) submodule. Clone and pull with `--recurse-submodules`, or use `git submodule update --init` once cloned. 

Alternatively you can set `git config submodule.recurse true` or `git config --global submodule.recurse true`.

## Building
```
mkdir build && cd build
cmake ..
make pico-midi2cv
```