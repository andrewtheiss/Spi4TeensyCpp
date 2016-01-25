// Spi4TeensyCpp.cpp : Defines the entry point for the console application.
//
#using <System.dll>
#include "stdafx.h"
#include "windows.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;

void loopForever()
{
	while(1) {}
}

// testConnection writes to the serial communication file handle
int testConnection(HANDLE serialComHandle) {
	
	char DataInitBuffer[] = "?";
	DWORD dwBytesToWrite = (DWORD)strlen(DataInitBuffer);
    DWORD dwBytesWritten = 0;

    BOOL bErrorWriteFlag = WriteFile( 
                    serialComHandle,           // open file handle
                    DataInitBuffer,      // start of data to write
                    dwBytesToWrite,  // number of bytes to write
                    &dwBytesWritten, // number of bytes that were written
                    NULL);            // no overlapped structure

    if (FALSE == bErrorWriteFlag)
    {
        Console::WriteLine("Terminal failure: Unable to write to COM.\n");
		loopForever();
    }
  
	Sleep(50);
	
	char  *chRead = new char[10];
	DWORD dwRead;
	BOOL bErrorReadFlag = ReadFile(
		serialComHandle, 
		chRead, 
		10,
		&dwRead, 
		NULL
	);
	
    if (FALSE == bErrorReadFlag)
    {
        Console::WriteLine("Terminal failure: Unable to read from COM.\n");
		loopForever();
    }

	Console::WriteLine(
		chRead[0] + 
		chRead[0] + 
		chRead[2] + 
		chRead[3] + 
		chRead[4] + 
		chRead[5] + 
		chRead[6] + 
		chRead[7]);

    return 1;
}

HANDLE openSerialConnection() {
	HANDLE serialComHandle;

	serialComHandle = CreateFile(
			L"\\\\.\\COM3",					// Cast to Long Pointer to Constant Wide String
			GENERIC_READ | GENERIC_WRITE,	// Read and write
			0, 
			0, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			0
		);

	
	if (serialComHandle == INVALID_HANDLE_VALUE) {
		// error opening port; abort
        Console::WriteLine("Error opening Port.  Abort.\n");
		loopForever();
	}

	return serialComHandle;
};


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
	

	HANDLE serialHandle = openSerialConnection();
	testConnection(serialHandle);

	while(1) {

	}
}

