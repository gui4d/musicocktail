#ifndef _SERIALCOM
#define _SERIALCOM

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
//#include <curses.h>
#include "ingredient.h"
#include "recipes.h"
#include "constants.h"

    int set_interface_attribs(int fd, int speed, int parity);
    void set_blocking(int fd, int should_block);
    int initSerial();
    int readSerial(int fd);
    int sendNewOrder(int idIngredient, int timeInDeciSec, int fd);
    int executeRecipe(RECIPE Recipe, int fd);
    int ConvertInDeciSec(float amount, int servoAdress);

    // BOOL OpenCOM(int nId);
    // BOOL CloseCOM();
    // BOOL ReadCOM(void *buffer, int nBytesToRead, int *pBytesRead);
    // BOOL WriteCOM(void *buffer, int nBytesToWrite, int *pBytesWritten);
#ifdef __cplusplus
}
#endif

#endif