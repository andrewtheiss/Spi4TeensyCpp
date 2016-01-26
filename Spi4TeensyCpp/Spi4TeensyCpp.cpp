// Spi4TeensyCpp.cpp : Defines the entry point for the console application.
//
#using <System.dll>
#include "stdafx.h"
#include "windows.h"
#include "Spi4TeensyOctoWS2811.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;



int _tmain(int argc, _TCHAR* argv[])
{
	array<String^>^ serialPorts = nullptr;
    try
    {
        // Get a list of serial port names.
        serialPorts = SerialPort::GetPortNames();
    }
    catch (Win32Exception^ ex)
    {
        Console::WriteLine(ex->Message);
    }

    Console::WriteLine("The following serial ports were found:");

    // Display each port name to the console.
    for each(String^ port in serialPorts)
    {
        Console::WriteLine(port);
    }
	
	Spi4TeensyOctoWS2811 * OpenGL2Serial = new Spi4TeensyOctoWS2811();
	OpenGL2Serial->openSerialConnection();

	if (OpenGL2Serial->testConnection()) {

	}


	while(1) {

	}
}

