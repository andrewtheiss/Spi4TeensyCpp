#using <System.dll>
#include "stdafx.h"
#include "windows.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;

#ifndef _SPI_4_TEENSY_OCTO_WS_2811_H_
#define _SPI_4_TEENSY_OCTO_WS_2811_H_

class Spi4TeensyOctoWS2811 {
	

public:
	Boolean testConnection();
	void openSerialConnection();
	void loopForever();
	Spi4TeensyOctoWS2811::Spi4TeensyOctoWS2811() {
	
		gamma = 1.7f;

		numPorts=0;  // the number of serial ports in use
		maxPorts=24; // maximum number of serial ports

		//Serial[] ledSerial = new Serial[maxPorts];     // each port's actual Serial port
		//Rectangle[] ledArea = new Rectangle[maxPorts]; // the area of the movie each port gets, in % (0-100)
		ledLayout = new boolean[maxPorts];   // layout of rows, true = even is left->right
		//PImage[] ledImage = new PImage[maxPorts];      // image sent to each port
		gammatable = new int[256];
		errorCount=0;
		framerate=0;
	}

private:
	float gamma;

	int numPorts;  // the number of serial ports in use
	int maxPorts; // maximum number of serial ports

	/*
	Serial * ledSerial;     // each port's actual Serial port
	Rectangle[] ledArea = new Rectangle[maxPorts]; // the area of the movie each port gets, in % (0-100)
	PImage[] ledImage = new PImage[maxPorts];      // image sent to each port
	*/

	boolean * ledLayout;

	int * gammatable;
	int errorCount;
	float framerate;

	HANDLE serialComHandle;
};


#endif