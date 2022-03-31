/* litSerie0.c : programme de lecture d'une interface serie */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

/* Definitions de MACRO */
#define ERROR -1
#define LBUF 256

/*******************************************************************
* Nom : UART_Open
* Entrees :   port : chemin complet du device
* Retour : OK = fd >= 0 sinon ERROR
*******************************************************************/
int UART_Open(char* port)
{
int fd;
    if ((fd = open(port, O_RDWR|O_NOCTTY|O_NDELAY)) == -1){
       perror("open");
       return ERROR;
    }
    if (fcntl(fd, F_SETFL, 0) < 0) {
       perror("fcntl");
       return ERROR;
    }
    if(!isatty(fd)) {
       printf("%s n'est pas un terminal !!\n",port);
       return ERROR;
    }
    return fd;
}

/*******************************************************************
* Nom : * UART_Close
* Entrees :   fd : File descriptor
* Retour : rien
*******************************************************************/
void UART_Close(int fd)
{
    close(fd);
}

/*******************************************************************
* Nom : * UART_Init() (cf man tcsetattr)
* Entrees :   fd : File descriptor
*          speed : Serial port speed
*       flowCtrl : Data flow control 0 Aucun, 1 hardware, 2 Soft
*       dbits    : de 5 a 8
*       stopb    : 1 ou 2
*       delai    : attente en lecture en 1/10e s
*       nbcmin   : nb de car. lu au minimum
*       parity   : N, E, O, S
* Retour : OK = 0 sinon ERROR
*******************************************************************/
#define NBSPEED 8
int UART_Init(int fd, int speed,int flowCtrl,int dbits,int stopb,
    int delai, int nbcmin, char parity)
{
int i;
int speed_arr[]={B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1800};
int valeur[]={115200, 57600, 38400, 19200, 9600, 4800, 2400, 1800};
struct termios options;

    if ( tcgetattr(fd,&options) != 0) {
        perror("tcgetattr");
        return(ERROR);
    }

    /* Mise en place des vitesse en entree et en sortie */
    for (i=0; i<NBSPEED; i++) {
        if (speed == valeur[i]) {
            cfsetispeed(&options, speed_arr[i]);
            cfsetospeed(&options, speed_arr[i]);
            break;
        }
    }
    if (i==NBSPEED) {
       fprintf(stderr,"Vitesse invalide = %d\n",speed);
       return(ERROR);
    }
    options.c_cflag |= CLOCAL; /* Ignore modem control lines */
    options.c_cflag |= CREAD; /* Enable receiver */

    /* pour les controles de flux */
    switch(flowCtrl) {
       case 0 : /* No flow control */
         options.c_cflag &= ~CRTSCTS;
         break;
       case 1 :/* Avec Hardware Flow Control */
         options.c_cflag |= CRTSCTS;
         break;
       case 2 :/* Software Flow Control */
         options.c_cflag |= IXON | IXOFF | IXANY;
         break;
    }

    options.c_cflag &= ~CSIZE; /* mise a zero de la zone character mask */
    switch (dbits) { /* a completer si besoin */
       case 8:
            options.c_cflag |= CS8;
            break;
       default:
            fprintf(stderr,"Erreur data size %d\n",dbits);
            return (ERROR);
    }

    /* controle de parite */
    switch (parity) {
       case 'n':
       case 'N': /*No parity bits */
            options.c_cflag &= ~PARENB;
            options.c_iflag &= ~INPCK;
            break;
       case 'o':
       case 'O': /* odd (impaire) */
            options.c_cflag |= (PARODD | PARENB);
            options.c_iflag |= INPCK;
            break;
       case 'e':
       case 'E': /* even (paire) */
            options.c_cflag |= PARENB;
            options.c_cflag &= ~PARODD;
            options.c_iflag |= INPCK;
            break;
       case 's':
       case 'S': /*Set to blank */
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
       default:
            fprintf(stderr,"Erreur parity %c\n",parity);
            return (ERROR);
    }

    /* parametre stop bits */
    switch (stopb) {
       case 1:
            options.c_cflag &= ~CSTOPB; break;
       case 2:
            options.c_cflag |= CSTOPB; break;
       default:
            fprintf(stderr,"Erreur stop bits %d\n",stopb);
            return (ERROR);
    }

    /* mode sans signaux et non canonique */
    options.c_lflag &= ~(ISIG | ICANON);
    /* reglage du mode non canonique */
    options.c_cc[VTIME] = delai;
    options.c_cc[VMIN] = nbcmin;

    /* on nettoie l'interface */
    tcflush(fd,TCIOFLUSH);

    /* Activation de la configuration */
    if (tcsetattr(fd,TCSANOW,&options) != 0) {
         perror("tcsetattr");
         return (ERROR);
    }
    return 0;
}

/*******************************************************************
* Nom : * UART_Recv
* Entree :    fd : File descriptor
*            buf : buffer de lecture
*            len : Longueur du buffer
* Retour : nb de car. lu ou ERROR
*******************************************************************/
int UART_Recv(int fd, char *buf,int len)
{
     return (read(fd,buf,len));
}

int main(int N, char *P[])
{
int fd, speed, n;
char rcv_buf[LBUF];

    if (N != 3) {
       printf("Utilisation: %s /dev/ttyXX vitesse_en_baud\n",P[0]);
       return 1;
    }
    if ((fd = UART_Open(P[1])) == ERROR) return 2;
    speed = atoi(P[2]);
    if (UART_Init(fd,speed, 0,8,1,0,1,'N') == ERROR) return 3;
    /* boucle de lecture */
    while (1) {
        n = UART_Recv(fd, rcv_buf,LBUF);
        if (n > 0) {
           rcv_buf[n] = '\0';
           printf("%s",rcv_buf);
        } else {
           fprintf(stderr,"Erreur lecture !!\n");
           break;
        }
    }
    UART_Close(fd);
    return 0;
}

