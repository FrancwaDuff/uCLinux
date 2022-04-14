#ifndef _LIB_SERIE_H_
#define _LIB_SERIE_H_

int UART_Open(char*);

void UART_Close(int);

int UART_Init(int, int, int, int, int, int, int, char);

int UART_Recv(int, char*, int);


#endif