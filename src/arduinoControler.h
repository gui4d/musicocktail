#ifndef _ARDUINOCONTROLER
#define _ARDUINOCONTROLER

#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "constants.h"

BOOL OpenCOM    (int nId);
BOOL CloseCOM   ();
BOOL ReadCOM    (void* buffer, int nBytesToRead, int* pBytesRead);
BOOL WriteCOM   (void* buffer, int nBytesToWrite, int* pBytesWritten);

#endif
