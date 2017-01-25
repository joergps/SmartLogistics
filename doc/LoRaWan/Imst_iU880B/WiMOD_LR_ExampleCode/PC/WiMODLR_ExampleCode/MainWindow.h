//------------------------------------------------------------------------------
//
//	File:		MainWindow.h
//
//	Abstract:	Main Window Class Declaration
//
//	Version:	0.1
//
//	Date:		02.02.2015
//
//	Disclaimer:	This example code is provided by IMST GmbH on an "AS IS" basis
//				without any warranties.
//
//------------------------------------------------------------------------------

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//------------------------------------------------------------------------------
//
//  Section Include Files
//
//------------------------------------------------------------------------------

#include <QMainWindow>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "WiMODLRHCI.h"
#include "KeyValueList.h"

//------------------------------------------------------------------------------
//
//  TMainWindow - Main Window Class
//
//------------------------------------------------------------------------------

class TMainWindow : public QMainWindow , public TWiMODLRHCIClient
{
    Q_OBJECT
    
public:
    explicit        TMainWindow(QWidget* parent = 0);
                    ~TMainWindow();
    
public slots:
    // handlers for connection handling
    void            cmdConnection_Open();
    void            cmdConnection_Close();
    void            cmdConnection_Query();

    // handlers for device management commands
    void            cmdDevice_Ping();
    void            cmdDevice_FactoryReset();
    void            cmdDevice_GetRadioConfiguration();
    void            cmdDevice_SetRadioConfiguration();

    // handlers for radiolink commands
    void            cmdRadioLink_SendUMessage();

private:
    // radio callback interface
    void            evRadio_ShowMessage(const QString& prefix, const QString& msg);
    void            evRadioLink_RxUMessage(const TWiMODLR_HCIMessage& rxMsg);


    // GUI creation helper functions
    void            CreateGUI();
    QPushButton*    CreatePushButton(const QString& title, const QString& toolTip, const QObject* receiver, const char* slot);
    QFrame*         CreateHLine();
    QTextEdit*      CreateLogWindow();

    // logging support
    void            ShowMessage(const QString& msg);
    void            ShowMessage(const QString& prefix, const QStringList& list);
    void            ShowLine();
    void            ShowCommand(const QString& cmd);
    void            ShowResult(const QString& result);
    void            ShowEvent(const QString& event, const QStringList& list);

    // timer support
    void            timerEvent(QTimerEvent* ev);

private:
    // Connection widgets (connection is implemneted via (virtual) serial comport)
    typedef struct
    {
        QComboBox*  ComPorts;
        QLineEdit*  Status;
    }TConnection;

    // Connection Instance
    TConnection     Connection;

    // Log Window Widgets
    typedef struct
    {
        QTextEdit*      Box;
        QCheckBox*      SingleLineOption;
    }TLogWindow;
    // Log Window Instance
    TLogWindow      LogWindow;

    // Radio Interface (WiMODLRHCI supports iM880A-L)
    TWiMODLRHCI     RadioIF;

    // Timer for comport polling
    int             TimerID;
    int             TimerPeriod;
};

#endif // MAINWINDOW_H

//------------------------------------------------------------------------------
// end
//------------------------------------------------------------------------------
