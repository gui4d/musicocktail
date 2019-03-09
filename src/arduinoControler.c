#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
 
/*=============================================================================
  Définition de constantes
=============================================================================*/
#define RX_SIZE         4096    /* taille tampon d'entrée  */
#define TX_SIZE         4096    /* taille tampon de sortie */
#define MAX_WAIT_READ   5000    /* temps max d'attente pour lecture (en ms) */
 
 
/*=============================================================================
  Variables globales.
=============================================================================*/
 
/* Handle du port COM ouvert */
HANDLE g_hCOM = NULL;
 
/* Délais d'attente sur le port COM */
COMMTIMEOUTS g_cto =
{
    MAX_WAIT_READ,  /* ReadIntervalTimeOut          */
    0,              /* ReadTotalTimeOutMultiplier   */
    MAX_WAIT_READ,  /* ReadTotalTimeOutConstant     */
    0,              /* WriteTotalTimeOutMultiplier  */
    0               /* WriteTotalTimeOutConstant    */
};
 
/* Configuration du port COM */
DCB g_dcb =
{
    sizeof(DCB),        /* DCBlength            */
    9600,               /* BaudRate             */
    TRUE,               /* fBinary              */
    FALSE,              /* fParity              */
    FALSE,              /* fOutxCtsFlow         */
    FALSE,              /* fOutxDsrFlow         */
    DTR_CONTROL_ENABLE, /* fDtrControl          */
    FALSE,              /* fDsrSensitivity      */
    FALSE,              /* fTXContinueOnXoff    */
    FALSE,              /* fOutX                */
    FALSE,              /* fInX                 */
    FALSE,              /* fErrorChar           */
    FALSE,              /* fNull                */
    RTS_CONTROL_ENABLE, /* fRtsControl          */
    FALSE,              /* fAbortOnError        */
    0,                  /* fDummy2              */
    0,                  /* wReserved            */
    0x100,              /* XonLim               */
    0x100,              /* XoffLim              */
    8,                  /* ByteSize             */
    NOPARITY,           /* Parity               */
    ONESTOPBIT,         /* StopBits             */
    0x11,               /* XonChar              */
    0x13,               /* XoffChar             */
    '?',                /* ErrorChar            */
    0x1A,               /* EofChar              */
    0x10                /* EvtChar              */
};
 

int main()
{
    /* variables locales */
    char buffer[256];
    int nId, nChoice, nBytesWritten, nBytesRead;
 
    /* demande du numéro du port COM */
    printf("Entrez le numero du port COM : ");
    scanf("%d", &nId);
 
    /* tentative d'ouverture */
    printf("Ouverture et configuration du port COM%d...\r\n", nId);
    if(!OpenCOM(nId)) return -1;
    printf("...OK\r\n");
 
    /* boucle tant que l'on ne quitte pas */
    do
    {
        /* menu */
        printf("\r\n");
        printf("1 : Envoyer des donnees.\r\n");
        printf("2 : Recevoir des donnees.\r\n");
        printf("3 : Quitter.\r\n");
        printf("Choix : ");
        scanf("%d", &nChoice);
 
        /* enoyer des données */
        if(nChoice == 1)
        {
            printf("\r\n");
            printf("Donnees a envoyer :\r\n");
            fflush(stdin);
            gets(buffer);
            printf("\r\n");
            printf("Envoi des donnees...\r\n");
            if(WriteCOM(buffer, strlen(buffer), &nBytesWritten))
                printf("%d octet(s) envoye(s).\r\n", nBytesWritten);
            else
                printf("Erreur lors de l'envoi.\r\n");
        }
 
        /* recevoir des données */
        if(nChoice == 2)
        {
            printf("\r\n");
            printf("Reception de donnees...\r\n");
            if(ReadCOM(buffer, sizeof(buffer)-1, &nBytesRead))
            {
                buffer[nBytesRead] = '\0';
                printf("%d octet(s) recu(s) :\r\n%s\r\n", nBytesRead, buffer);
            }
            else
                printf("Erreur lors de la réception.\r\n");
        }
    }while(nChoice != 3);
 
    /* fermeture du port COM et retour */
    CloseCOM();
    return 0;
}
 
/******************************************************************************
  OpenCOM : ouverture et configuration du port COM.
  entrée : nId : Id du port COM à ouvrir.
  retour : vrai si l'opération a réussi, faux sinon.
******************************************************************************/
BOOL OpenCOM(int nId)
{
    /* variables locales */
    char szCOM[16];
 
    /* construction du nom du port, tentative d'ouverture */
    sprintf(szCOM, "COM%d", nId);
    g_hCOM = CreateFile(szCOM, GENERIC_READ|GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, FILE_ATTRIBUTE_SYSTEM, NULL);
    if(g_hCOM == INVALID_HANDLE_VALUE)
    {
        printf("Erreur lors de l'ouverture du port COM%d", nId);
        return FALSE;
    }
 
    /* affectation taille des tampons d'émission et de réception */
    SetupComm(g_hCOM, RX_SIZE, TX_SIZE);
 
    /* configuration du port COM */
    if(!SetCommTimeouts(g_hCOM, &g_cto) || !SetCommState(g_hCOM, &g_dcb))
    {
        printf("Erreur lors de la configuration du port COM%d", nId);
        CloseHandle(g_hCOM);
        return FALSE;
    }
 
    /* on vide les tampons d'émission et de réception, mise à 1 DTR */
    PurgeComm(g_hCOM, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_TXABORT|PURGE_RXABORT);
    EscapeCommFunction(g_hCOM, SETDTR);
    return TRUE;
}
 
/******************************************************************************
  CloseCOM : fermeture du port COM.
  retour : vrai si l'opération a réussi, faux sinon.
******************************************************************************/
BOOL CloseCOM()
{
    /* fermeture du port COM */
    CloseHandle(g_hCOM);
    return TRUE;
}
 
/******************************************************************************
  ReadCOM : lecture de données sur le port COM.
  entrée : buffer       : buffer où mettre les données lues.
           nBytesToRead : nombre max d'octets à lire.
           pBytesRead   : variable qui va recevoir le nombre d'octets lus.
  retour : vrai si l'opération a réussi, faux sinon.
-------------------------------------------------------------------------------
  Remarques : - la constante MAX_WAIT_READ utilisée dans la structure
                COMMTIMEOUTS permet de limiter le temps d'attente si aucun
                caractères n'est présent dans le tampon d'entrée.
              - la fonction peut donc retourner vrai sans avoir lu de données.
******************************************************************************/
BOOL ReadCOM(void* buffer, int nBytesToRead, int* pBytesRead)
{
    return ReadFile(g_hCOM, buffer, nBytesToRead, pBytesRead, NULL);
}
 
/******************************************************************************
  WriteCOM : envoi de données sur le port COM.
  entrée : buffer        : buffer avec les données à envoyer.
           nBytesToWrite : nombre d'octets à envoyer.
           pBytesWritten : variable qui va recevoir le nombre d'octets
                           envoyés.
  retour : vrai si l'opération a réussi, faux sinon.
******************************************************************************/
BOOL WriteCOM(void* buffer, int nBytesToWrite, int* pBytesWritten)
{
    /* écriture sur le port */
    return WriteFile(g_hCOM, buffer, nBytesToWrite, pBytesWritten, NULL);
}