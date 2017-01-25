//------------------------------------------------------------------------------
//
//	File:		main.cpp
//
//	Abstract:	Program entry function
//
//	Version:	0.1
//
//	Date:		09.02.2015
//
//	Disclaimer:	This example code is provided by IMST GmbH on an "AS IS" basis
//				without any warranties.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  Include Files
//
//------------------------------------------------------------------------------

#include <QApplication>
#include "MainWindow.h"


//------------------------------------------------------------------------------
//
//  main
//
//  @brief: program main entry function
//
//------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    // create Qt application class
    QApplication a(argc, argv);

    // create main window
    TMainWindow w;

    // show main window
    w.show();

    // run Qt application
    return a.exec();
}
//------------------------------------------------------------------------------
// end of file
//------------------------------------------------------------------------------
