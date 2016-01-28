#include "stdafx.h"
#include "Spi4TeensyOctoWS2811.h"

Boolean Spi4TeensyOctoWS2811::TestConnection() {
	
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
		LoopForever();
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
		LoopForever();
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

void Spi4TeensyOctoWS2811::OpenSerialConnection() {

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
		LoopForever();
	}
};

void Spi4TeensyOctoWS2811::LoopForever()
{
	while(1) {}
}

void Spi4TeensyOctoWS2811::Image2data(PImage image, byte *data, boolean layout) {
  int offset = 3;
  int x, y, xbegin, xend, xinc, mask;
  int linesPerPin = image.height / 8;
  int * pixel = new int[8];
  
  for (y = 0; y < linesPerPin; y++) {
    if ((y & 1) == (layout ? 0 : 1)) {
      // even numbered rows are left to right
      xbegin = 0;
      xend = image.width;
      xinc = 1;
    } else {
      // odd numbered rows are right to left
      xbegin = image.width - 1;
      xend = -1;
      xinc = -1;
    }
    for (x = xbegin; x != xend; x += xinc) {
      for (int i=0; i < 8; i++) {
        // fetch 8 pixels from the image, 1 for each pin
        pixel[i] = image.pixels[x + (y + linesPerPin * i) * image.width];
        pixel[i] = ColorWiring(pixel[i]);
      }
      // convert 8 pixels to 24 bytes
      for (mask = 0x800000; mask != 0; mask >>= 1) {
        byte b = 0;
        for (int i=0; i < 8; i++) {
          if ((pixel[i] & mask) != 0) b |= (1 << i);
        }
        data[offset++] = b;
      }
    }
  } 
}

int Spi4TeensyOctoWS2811::ColorWiring(int c) {
  int red = (c & 0xFF0000) >> 16;
  int green = (c & 0x00FF00) >> 8;
  int blue = (c & 0x0000FF);
  red = gammatable[red];
  green = gammatable[green];
  blue = gammatable[blue];
  return (green << 16) | (red << 8) | (blue); // GRB - most common wiring
}

int Spi4TeensyOctoWS2811::PercentageInverse(int num, int percent) {
  double div = PercentageFloat(percent);
  double output = num / div;
  return (int)output;
}

double Spi4TeensyOctoWS2811::PercentageFloat(int percent) {
  if (percent == 33) return 1.0 / 3.0;
  if (percent == 17) return 1.0 / 6.0;
  if (percent == 14) return 1.0 / 7.0;
  if (percent == 13) return 1.0 / 8.0;
  if (percent == 11) return 1.0 / 9.0;
  if (percent ==  9) return 1.0 / 11.0;
  if (percent ==  8) return 1.0 / 12.0;
  return (double)percent / 100.0;
}

void Spi4TeensyOctoWS2811::Draw() {
  // show the original video

	/*
  image(myMovie, 0, 80);
  
  // then try to show what was most recently sent to the LEDs
  // by displaying all the images for each port.
  for (int i=0; i < numPorts; i++) {
    // compute the intended size of the entire LED array
    int xsize = percentageInverse(ledImage[i].width, ledArea[i].width);
    int ysize = percentageInverse(ledImage[i].height, ledArea[i].height);
    // computer this image's position within it
    int xloc =  percentage(xsize, ledArea[i].x);
    int yloc =  percentage(ysize, ledArea[i].y);
    // show what should appear on the LEDs
    image(ledImage[i], 240 - xsize / 2 + xloc, 10 + yloc);
  } 
  */
}

void Spi4TeensyOctoWS2811::WriteFrame() {

	// Get OpenGL framebuffer here

	// TODO - NEED TO THROTTLE THIS MANUALY TO MAKE SURE DATA RATE IS NOT EXCEEDED!
	framerate = 30.0; // TODO, how to read the frame rate???
	//PImage m;

	for (int i=0; i < numPorts; i++) {    
		// copy a portion of the movie's image to the LED image
		/*
		int xoffset = percentage(m.width, ledArea[i].x);
		int yoffset = percentage(m.height, ledArea[i].y);
		int xwidth =  percentage(m.width, ledArea[i].width);
		int yheight = percentage(m.height, ledArea[i].height);
		ledImage[i].copy(m, xoffset, yoffset, xwidth, yheight,
							0, 0, ledImage[i].width, ledImage[i].height);
							*/
		// convert the LED image to raw data
		byte * ledData;
		int dataLength = (ledImage[i].width * ledImage[i].height * 3) + 3;
		dataLength = 80 * 8 * 3 + 3;
		ledData =  new byte[dataLength];

		for (int j=3; j<dataLength; j++) {
			ledData[j] = 0;
			if (j%8 == 0) {
				ledData[j] = 0;
			}
		}
		
		//  Write a single 6 pixels on the first row only
		ledData[11] = 255;
		ledData[35] = 255;
		ledData[67] = 255;
		ledData[71] = 255;
		ledData[91] = 255;
		ledData[99] = 255;
		ledData[123] = 255;

		//image2data(ledImage[i], ledData, ledLayout[i]);
		if (i == 0) {
			ledData[0] = '*';  // first Teensy is the frame sync master
			int usec = (int)((1000000.0 / framerate) * 0.75);
			ledData[1] = (byte)(usec);   // request the frame sync pulse
			ledData[2] = (byte)(usec >> 8); // at 75% of the frame time
		} else {
			ledData[0] = '%';  // others sync to the master board
			ledData[1] = 0;
			ledData[2] = 0;
		}

		// send the raw data to the LEDs  :-)
		// WRITE TO SERIAL PORT
		DWORD dwBytesToWrite = (DWORD)dataLength;
		DWORD dwBytesWritten = 0;

		BOOL bErrorWriteFlag = WriteFile( 
						serialComHandle,           // open file handle
						ledData,      // start of data to write
						dwBytesToWrite,  // number of bytes to write
						&dwBytesWritten, // number of bytes that were written
						NULL);            // no overlapped structure

		if (FALSE == bErrorWriteFlag)
		{
			Console::WriteLine("Terminal failure: Unable to write to COM.\n");
			LoopForever();
		}
  
		//ledSerial[i].write(ledData); 
	}
}