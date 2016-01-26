#include "stdafx.h"
#include "Spi4TeensyOctoWS2811.h"

Boolean Spi4TeensyOctoWS2811::testConnection() {
	
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
		chRead[1] + 
		chRead[2] + 
		chRead[3] + 
		chRead[4] + 
		chRead[5] + 
		chRead[6] + 
		chRead[7]);

	return true;
}

void Spi4TeensyOctoWS2811::openSerialConnection() {

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
};

void Spi4TeensyOctoWS2811::loopForever()
{
	while(1) {}
}

