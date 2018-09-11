#ifndef _SERIALCOM
#define _SERIALCOM

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include"ingredient.h"

int sendNewOrder(INGREDIENT Ingredient, float quantitee);

#ifdef __cplusplus
}
#endif

#endif