-------------------------------------
   WiMODLRHCI Example Code
   2015 IMST GmbH
-------------------------------------

----------------------------------------------------------------------------------------------------------

.1 Content:
----------------------------------------------------------------------------------------------------------

This C++ example code project shows how to implement the WiMOD LR HCI
(Long Range Host Controller Interface) Protocol used by serveral WiMOD radio modules:
(iM880A, iC880A, iM881A, ...)

The code is implemented by means of Qt Creator (3.0.1) and the free available Qt framework (5.2.1).

This project can be compiled for Windows / Linux and MAC OS X desktop operating systems.

----------------------------------------------------------------------------------------------------------

.2 Revision History:
--------------------------------------------------------------------------

16.02.2015
    - First release as a complete Qt project

----------------------------------------------------------------------------------------------------------

.3 Files & Folders
----------------------------------------------------------------------------------------------------------

- /WiMODLR
    |- WiMODLRHCI_IDs.h - WiMODLR HCI Message Identifier
    |- WiMODLRHCI.h     - WiMODLR HCI Wrapper Class Declaration
    |- WiMODLRHCI.cpp   - WiMODLR HCI Wrapper Class Implementation
    |- WMDefs.h         - general WiMOD declarations

- /Utils
    |- CRC16.h          - CRC16 Declaration
    |- CRC16.cpp        - CRC16 Implementation
    |- ComSlip.h        - SLIP Wrapper Class Declaration
    |- ComSlip.cpp      - SLIP Wrapper Class Implementation
    |- SerialDevice.h   - Serial Device Wrapper Class Declaration
    |- SerialDevice.cpp - Serial Device Wrapper Class Implementation
    |- RegistryKey.h    - Windows Registry Helper Class Declaration
    |- RegistryKey.cpp  - Windows Registry Helper Class Implementation
    |- KeyValueList.h   - Key-Value-List Helper Class Declaration
    |- KeyValueList.cpp - Key-Value-List Helper Class Implementation

- /
  |- main.cpp                  - program entry function
  |- MainWindow.h              - Main Window Class Declaration
  |- MainWindow.cpp            - Main Window Class Implementation
  |- WiMODLR_ExampleCode.pro   - Qt Creator project file
  |- readme.txt                - this file

---------------------------------------------------------------------------------------------------------------------------
end of release nodes
---------------------------------------------------------------------------------------------------------------------------
