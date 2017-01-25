#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T16:39:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


INCLUDEPATH += ../WiMODLR_ExampleCode
INCLUDEPATH += ../WiMODLR_ExampleCode/WiMODLR
INCLUDEPATH += ../WiMODLR_ExampleCode/Utils

TARGET = WiMODLR_ExampleCode
TEMPLATE = app


SOURCES += main.cpp\
    MainWindow.cpp \
    Utils/ComSlip.cpp \
    Utils/CRC16.cpp \
    WiMODLR/WiMODLRHCI.cpp \
    Utils/RegistryKey.cpp \
    Utils/SerialDevice.cpp \
    Utils/KeyValueList.cpp

HEADERS  += \
    MainWindow.h \
    Utils/ComSlip.h \
    Utils/CRC16.h \
    WiMODLR/WiMODLRHCI.h \
    WiMODLR/WiMODLRHCI_IDs.h \
    WiMODLR/WMDefs.h \
    Utils/RegistryKey.h \
    Utils/SerialDevice.h \
    Utils/KeyValueList.h

#FORMS    += mainwindow.ui

OTHER_FILES += \
    readme.txt
