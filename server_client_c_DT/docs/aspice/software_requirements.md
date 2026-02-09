# Software Requirements Specification (SWE.1)

## 1. Traceability
Derived from System Requirements (SYS.1).

## 2. Functional Software Requirements

| ID | Description | Parent System Req |
| :--- | :--- | :--- |
| **SWE_SRV_001** | The server program shall listen for incoming TCP connections. | SYS_REQ_001, SYS_REQ_002 |
| **SWE_SRV_002** | The server shall accept a port number via the `-p` flag. | SYS_REQ_004 |
| **SWE_SRV_003** | The server shall default to port 8080 if not specified. | SYS_REQ_004 |
| **SWE_SRV_004** | The server shall validate port inputs (1-65535). | SYS_REQ_004 |
| **SWE_SRV_005** | The server shall retrieve the host system's current time. | SYS_REQ_001 |
| **SWE_SRV_006** | The server shall send the time string to the client. | SYS_REQ_001 |
| **SWE_CLI_001** | The client program shall connect to a server via TCP. | SYS_REQ_001, SYS_REQ_002 |
| **SWE_CLI_002** | The client shall accept a target IP via the `-i` flag. | SYS_REQ_004 |
| **SWE_CLI_003** | The client shall accept a target port via the `-p` flag. | SYS_REQ_004 |
| **SWE_CLI_004** | The client shall display the received string. | SYS_REQ_001 |

## 3. Non-Functional Software Requirements

| ID | Description | Parent System Req |
| :--- | :--- | :--- |
| **SWE_NFR_001** | The software shall be implemented in C99. | SYS_REQ_003 |
| **SWE_NFR_002** | Shared logic shall be encapsulated in a common library. | N/A (Arch Decision) |
