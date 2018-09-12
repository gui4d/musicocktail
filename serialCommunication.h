#ifndef _SERIALCOM
#define _SERIALCOM

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include"ingredient.h"
#include "recipes.h"

int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);
int initSerial();
int readSerial(int fd);
int sendNewOrder(INGREDIENT Ingredient, float quantitee,int fd);
int executeRecipe(RECIPE Recipe , int fd );

#ifdef __cplusplus
}
#endif

#endif