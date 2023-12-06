#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include<semaphore.h>

char *datachar;
void *charI_thread(void *vargp);
void *charO_thread(void *vargp);
void *charU_thread(void *vargp);
void *concatResult(void *vargp);
char *helper_node(char *data, int len);
void *charA_thread(void *vargp);
void *charE_thread(void *vargp);
void * doRecieving(void * sockID);
void *doNetworking(void *ClientDetail) ;
unsigned long binaryToDecimal(char *binary, int length);
void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);
char *crc_remainder(char *binary, int binaryLength, char *polynomial);
char *Hammig(int dataLength, char *data);
int crc_error_detection(char *binary, int binaryLength, char *polynomial);
char *Hamming_Detection_Correction(int dataLength, char *hammingcode);
