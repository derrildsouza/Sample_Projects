# Client-Server Date/Time Application

This repository contains two implementations of a TCP Client-Server application for date/time retrieval, following the ASPICE process.

## Implementations

### 1. [C Implementation (c_program)](c_program/)
The original implementation in standard C99.
- **Features**: Modular design, shared library, robust error handling.
- **Build System**: CMake.
- **Testing**: Google Test (C++ wrapper).

### 2. [C++ Implementation (cpp_program)](cpp_program/)
A modern C++17 port of the application.
- **Features**: Object-oriented design (`TimeServer`, `TimeClient` classes), RAII resource management, Exception handling.
- **Build System**: CMake.
- **Testing**: Google Test.

## Documentation
Both projects adhere to the same requirements and architecture guidelines:
- [System Requirements (SYS.1)](server_client_cpp_DT/docs/aspice/architecture.md)
- [Software Requirements (SWE.1)](server_client_cpp_DT/docs/aspice/software_requirements.md)
- [Architecture & Design (SWE.2/3)](server_client_cpp_DT/docs/aspice/architecture.md)
- [Traceability Matrix (SWE.4/5)](server_client_cpp_DT/docs/aspice/traceability_matrix.md)

## Quick Start
To build both projects:

```bash
# Build C Program
cd c_program
mkdir -p build && cd build
cmake .. && make

# Build C++ Program
cd ../../cpp_program
mkdir -p build && cd build
cmake .. && make
```
