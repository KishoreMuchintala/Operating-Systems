#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<ctype.h>
#include<sys/wait.h>


void decision_function( char *data, char *function, FILE *fileName);

void data_linker( char *argv1,char *argv2,char *argv3);
void char_to_binary(char character, FILE *fp);
void binary_to_char(char *binary, FILE *fp);


void Framing(char *data, char *fileName);
void Deframing(char *data, char *fileName);
