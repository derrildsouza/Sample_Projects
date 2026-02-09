# C++ Client-Server Application

A modern C++17 implementation of the Date/Time Client-Server application.

## Structure
- **[server/](server/)**: Server implementation using `TimeServer` class.
- **[client/](client/)**: Client implementation using `TimeClient` class.
- **[common/](common/)**: Shared utility library (`libcommon_cpp`).
- **[test/](test/)**: Google Test suite.
- **[docs/](docs/)**: ASPICE documentation.

## Prerequisites
- CMake 3.10+
- C++17 compliant compiler (GCC/Clang)
- Google Test (GTest)

## Build & Run

### 1. Build
```bash
mkdir -p build
cd build
cmake ..
make
```

### 2. Run Tests
```bash
./test/test_runner_cpp
```

### 3. Run Application
**Start Server:**
```bash
./server/server_cpp -p 8080
```

**Run Client:**
```bash
./client/client_cpp -i 127.0.0.1 -p 8080
```

## Features
- **RAII**: Sockets are automatically closed when objects go out of scope.
- **Exceptions**: Proper C++ exception handling for error conditions.
- **Type Safety**: Stronger type safety compared to the C version.
