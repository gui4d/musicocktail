
#include "serialCommunication.h"

int sendNewOrder(INGREDIENT Ingredient, float amount){
    FILE *serialPort;
    long int data = 10000*ingredient->servoAdress + (int)(amount);
    
    serialPort = fopen(ARDUINOADRESS,"w");  //Opening device file
    fprintf(serialPort,"%ld",data); //Writing to the file
    fprintf(serialPort,"%c","\n"); //end of transmission
    fclose(file);
}