# C Histogram

Command-line histogram program implemented in C using signal handling, standard I/O, and array-based data processing.

## Overview

This program reads byte values from standard input and tracks their frequency using a 256-element histogram. The resulting histogram can be displayed in the terminal or written to a file when specific signals are received.

The program processes input until EOF and supports signal-based histogram output and program termination.

## Features

- Byte frequency counting for values 0–255
- Histogram generation and formatted output
- Standard input processing
- Signal handling with SIGUSR1, SIGINT, and SIGTERM
- Histogram output to a file
- ASCII-based histogram bars
- File I/O using standard C library functions
- EOF-based program termination

## Technologies

- C
- Linux/Unix
- Standard I/O
- File I/O
- Signal Handling
- Arrays

## How It Works

The program maintains a 256-element histogram where each index represents a byte value.

As input is read from standard input, the corresponding histogram entry is incremented:

## Academic Context
This project was completed as part of Penn State's CMPSC 311 coursework.
