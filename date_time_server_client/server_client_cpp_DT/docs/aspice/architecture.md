# Software Architecture & Detailed Design (SWE.2/SWE.3) - C++ Version

## 1. System Overview
The system follows a classic Client-Server architecture using TCP/IP sockets, implemented in C++17.

## 2. Component View

### 2.1 Common Module (`libcommon_cpp`)
- **Description**: Shared library containing utility functions and constants.
- **Responsibilities**: 
    - Argument parsing (using `common::parse_arguments` returning `common::Arguments` struct).
    - Constant definitions (Ports, Buffer sizes) in `common` namespace.
- **Interfaces**:
    - `common::Arguments parse_arguments(argc, argv)`
- **Traceability**: Implements `REQ_NFR_002`, `SWE_SRV_002`, `SWE_CLI_002`, `SWE_SRV_004`, `SWE_CLI_004`.

### 2.2 Server Module (`server_cpp`)
- **Description**: The passive entity that listens for connections.
- **Class**: `TimeServer`
- **Responsibilities**:
    - Initialize socket (RAII managed).
    - Accept connections.
    - Generate Time String.
    - Send Data.
- **Dependencies**: `libcommon_cpp`.
- **Traceability**: Implements `SWE_SRV_001` to `SWE_SRV_006`.

### 2.3 Client Module (`client_cpp`)
- **Description**: The active entity that initiates requests.
- **Class**: `TimeClient`
- **Responsibilities**:
    - Initialize socket (RAII managed).
    - Connect to Server.
    - Receive Data.
    - Print Data.
- **Dependencies**: `libcommon_cpp`.
- **Traceability**: Implements `SWE_CLI_001` to `SWE_CLI_005`.

## 3. Dynamic View (Sequence)
Essentially same as C version, but method calls replace function calls.
