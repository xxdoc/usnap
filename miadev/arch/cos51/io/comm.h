#ifndef COS51_COMM_H
#define COS51_COMM_H

#include "../types.h"
#include "baud.h"

#ifdef COMM_BUFSIZE
__xdata char sendbuf[COMM_BUFSIZE];
__xdata char recvbuf[COMM_BUFSIZE];
byte sendbuf_size = COMM_BUFSIZE;
byte recvbuf_size = COMM_BUFSIZE;
#endif

void commSerialProc() __interrupt(INT_UART);

typedef bool (*TimeoutProc)();

extern TimeoutProc timeout_proc;

bool send(char ch);
char recv();

/**
 * @return the actual bytes sent if timeout.
 */
word sendblob(char *buf, word size);

/**
 * @return the actual bytes received if timeout.
 */
word recvblob(char *buf, word size);

byte available();

void flush();

#endif
