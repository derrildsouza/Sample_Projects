# Software Architecture & Detailed Design (SWE.2/SWE.3)

## 1. System Overview
The system follows a classic Client-Server architecture using TCP/IP sockets.

## 2. Component View

### 2.1 Common Module (`libcommon`)
- **Description**: Shared library containing utility functions and constants.
- **Responsibilities**: 
    - Argument parsing.
    - Constant definitions (Ports, Buffer sizes).
- **Interfaces**:
    - `parse_arguments(argc, argv, ip, port)`
- **Traceability**: Implements `REQ_NFR_002`, `REQ_SRV_002`, `REQ_CLI_002`, `REQ_SRV_004`, `REQ_CLI_004`.

### 2.2 Server Module (`server`)
- **Description**: The passive entity that listens for connections.
- **Responsibilities**:
    - Initialize socket (Socket -> Bind -> Listen).
    - Accept connections.
    - Generate Time String.
    - Send Data.
- **Dependencies**: `libcommon`.
- **Traceability**: Implements `REQ_SRV_001` to `REQ_SRV_006`.

### 2.3 Client Module (`client`)
- **Description**: The active entity that initiates requests.
- **Responsibilities**:
    - Initialize socket.
    - Connect to Server.
    - Receive Data.
    - Print Data.
- **Dependencies**: `libcommon`.
- **Traceability**: Implements `REQ_CLI_001` to `REQ_CLI_005`.

## 3. Dynamic View (Sequence)
See `README.md` for the Sequence Diagram.
