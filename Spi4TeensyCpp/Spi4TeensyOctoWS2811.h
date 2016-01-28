#using <System.dll>
#include "stdafx.h"
#include "windows.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;

#ifndef _SPI_4_TEENSY_OCTO_WS_2811_H_
#define _SPI_4_TEENSY_OCTO_WS_2811_H_


struct PImage {
	u_int height;
	u_int width;
	u_int * pixels;
};

struct Rectangle {


};

class Spi4TeensyOctoWS2811 {
	

public:
	Boolean TestConnection();
	void OpenSerialConnection();
	void LoopForever();
	void Image2data(PImage, byte[], boolean);
	int ColorWiring(int);
	int PercentageInverse(int, int);
	double PercentageFloat(int);
	void Draw();
	void WriteFrame();

	Spi4TeensyOctoWS2811::Spi4TeensyOctoWS2811() {
	
		gamma = 1.7f;

		numPorts=1;  // the number of serial ports in use
		maxPorts=24; // maximum number of serial ports

		//Serial[] ledSerial = new Serial[maxPorts];     // each port's actual Serial port
		//Rectangle[] ledArea = new Rectangle[maxPorts]; // the area of the movie each port gets, in % (0-100)
		ledLayout = new boolean[maxPorts];   // layout of rows, true = even is left->right
		ledImage = new PImage[maxPorts];      // image sent to each port
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
	PImage[] ledImage = new PImage[maxPorts];   
	*/

	boolean * ledLayout;
	PImage * ledImage;		   // image sent to each port

	int * gammatable;
	int errorCount;
	float framerate;

	HANDLE serialComHandle;
};


#endif