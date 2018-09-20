#include "serialCommunication.h"

int initSerial(){
        int fd = open (ARDUINOADRESS, O_RDWR | O_NOCTTY | O_SYNC);
        if (fd < 0)
        {
                printf("error %d opening %s: %s\n", errno, ARDUINOADRESS, strerror (errno));
                return 0;
        }
        set_interface_attribs (fd, B9600, 0);  // set speed to 115,200 bps, 8n1 (no parity)
        set_blocking (fd, 0);               // set no blocking
        int i;
                for( i = 0 ; i< 5 ; i++){
                readSerial(fd);
        }
        return fd;

}

int readSerial(int fd){
        int n;
        char buf[5000];
        memset(buf,0,sizeof buf);
        n = read (fd, buf, sizeof buf);  // read up to 100 characters if ready to read
        if(n){
            printf("%s",buf);
        }
        return n ;
}

int set_interface_attribs (int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // disable break processing
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf("error %d setting term attributes", errno);
}

int sendNewOrder(INGREDIENT Ingredient, float amount, int fd)
{
    if(Ingredient->servoAdress > -1 && Ingredient->servoAdress < 16 ){
        char Data[7];
        unsigned int i;
        for (i = 0 ; i< sizeof(Data); i++){
                Data[i]='0';
        }
        switch(Ingredient->servoAdress){
                case 0: break;
                case 1: Data[1]='1';break;
                case 2: Data[1]='2';break;
                case 3: Data[1]='3';break;
                case 4: Data[1]='4';break;
                case 5: Data[1]='5';break;
                case 6: Data[1]='6';break;
                case 7: Data[1]='7';break;
                case 8: Data[1]='8';break;
                case 9: Data[1]='9';break;
                case 10: Data[0]='1';break;
                case 11: Data[0]='1';Data[1]='1';break;
                case 12: Data[0]='1';Data[1]='2';break;
                case 13: Data[0]='1';Data[1]='3';break;
                case 14: Data[0]='1';Data[1]='4';break;
                case 15: Data[0]='1';Data[1]='5';break;
                default :  return 0;
        }
        switch((int)amount/1000%10){
                case 0: break;
                case 1: Data[2]='1';break;
                case 2: Data[2]='2';break;
                case 3: Data[2]='3';break;
                case 4: Data[2]='4';break;
                case 5: Data[2]='5';break;
                case 6: Data[2]='6';break;
                case 7: Data[2]='7';break;
                case 8: Data[2]='8';break;
                case 9: Data[2]='9';break;
        }
        switch((int)amount/100%10){
                case 0: break;
                case 1: Data[3]='1';break;
                case 2: Data[3]='2';break;
                case 3: Data[3]='3';break;
                case 4: Data[3]='4';break;
                case 5: Data[3]='5';break;
                case 6: Data[3]='6';break;
                case 7: Data[3]='7';break;
                case 8: Data[3]='8';break;
                case 9: Data[3]='9';break;
        }
        switch((int)amount/10%10){
                case 0: break;
                case 1: Data[4]='1';break;
                case 2: Data[4]='2';break;
                case 3: Data[4]='3';break;
                case 4: Data[4]='4';break;
                case 5: Data[4]='5';break;
                case 6: Data[4]='6';break;
                case 7: Data[4]='7';break;
                case 8: Data[4]='8';break;
                case 9: Data[4]='9';break;
        }
        switch((int)amount%10){
                case 0: break;
                case 1: Data[5]='1';break;
                case 2: Data[5]='2';break;
                case 3: Data[5]='3';break;
                case 4: Data[5]='4';break;
                case 5: Data[5]='5';break;
                case 6: Data[5]='6';break;
                case 7: Data[5]='7';break;
                case 8: Data[5]='8';break;
                case 9: Data[5]='9';break;
        }
        printf("%s\n",Data);
        write (fd, Data, 7);           // send 7 character greeting
        usleep ((7 + 25) * 100);             // sleep enough to transmit the 7 plus
        return 1;
    }
    else{
        printf("[warning] ask to use non asigned drink");
        return 0 ;
    }
}

int executeRecipe(RECIPE Recipe , int fd ){
        int i; 
        for (i = 0 ; i < Recipe->nbIngredients; i ++){
                sendNewOrder(ingredient(Recipe->listIddIngredients[i]), Recipe->listAmount[i],fd);
        }
        return 1;

}




