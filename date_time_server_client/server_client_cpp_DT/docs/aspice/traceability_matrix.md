# Test Specification & Traceability Matrix (SWE.4/SWE.5)

## 1. Requirement Traceability (SYS.1 -> SWE.1 -> SWE.3 -> Code)

| System Req | Software Req | Design Component | Code Unit | Test Case ID |
| :--- | :--- | :--- | :--- | :--- |
| **SYS_REQ_004** | **SWE_SRV_002** | Common Module | `common.c:parse_arguments` | `TEST_ARG_001` |
| **SYS_REQ_004** | **SWE_SRV_003** | Common Module | `common.h:DEFAULT_PORT` | `TEST_ARG_003` |
| **SYS_REQ_004** | **SWE_SRV_004** | Common Module | `common.c:parse_arguments` | `TEST_ARG_004` |
| **SYS_REQ_004** | **SWE_CLI_002** | Common Module | `common.c:parse_arguments` | `TEST_ARG_001` |
| **SYS_REQ_001** | **SWE_SRV_006** | Server Module | `server.c:main` | `TEST_SYS_001` |

## 2. Test Specifications

### Unit Tests (Automated GTest)

| Test ID | Name | Description | Verified Requirement |
| :--- | :--- | :--- | :--- |
| **TEST_ARG_001** | `ValidInput_IP_Port` | Verifies parsing valid -i and -p flags. | `SWE_CLI_002`, `SWE_SRV_002` |
| **TEST_ARG_002** | `ValidInput_PortOnly` | Verifies parsing valid -p flag. | `SWE_SRV_002` |
| **TEST_ARG_003** | `ValidInput_IPOnly` | Verifies default port usage. | `SWE_SRV_003` |
| **TEST_ARG_004** | `InvalidInput_PortRangeHigh` | Verifies rejection of port > 65535. | `SWE_SRV_004` |
| **TEST_ARG_005** | `InvalidInput_PortRangeLow` | Verifies rejection of port < 1. | `SWE_SRV_004` |
| **TEST_ARG_006** | `InvalidInput_PortNonNumeric` | Verifies rejection of non-numeric ports. | `SWE_CLI_004` |

### System Tests (Manual / Scripted)

| Test ID | Description |
| :--- | :--- |
| **TEST_SYS_001** | Start server, run client, verify date string is printed. |
