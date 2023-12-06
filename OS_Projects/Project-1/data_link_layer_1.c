#include"encDec.h"

void data_linker( char *argv1,char *argv2,char *argv3){

	if (strcmp(argv2,"framing") == 0){
		Framing(argv1,argv3);
	}
	else if (strcmp(argv2,"deframing") == 0) {
		Deframing(argv1,argv3);
	}
}

void Framing(char *data, char *fileName){

	long length = strlen(data);
	char frame[67];
	long i,j,k=0;
	FILE *fp  = fopen(fileName,"wb");
		
	for (i =0; i < length/64; i++ ){
		strcpy(frame,"");
		frame[0] = 22;
		frame[1] = 22;

		k = 2;
		frame[k++] = 64;
		for (j = i*64 ; j < (i+1)*64 ; j++ ) {
			frame[k++] = data[j]; 
		}
		decision_function(frame,"ctob",fp);
		
		/*for (int p = 3;p<67;p++){
		printf("%c",frame[p]);
		}*/

	}
	strcpy(frame,"");
	frame[0] = 22;
	frame[1] = 22;
	k = 2;
	frame[k++] = length - j+2;
	for (j = j ; j < length ; j++ ) {
		frame[k++] = data[j];
	}
	decision_function(frame,"ctob",fp);
	fclose(fp);
		/*for (int p = 3;p<frame[2];p++){
		printf("%c",frame[p]);
		}*/
}

void Deframing(char *data, char *fileName){
long length = strlen(data);

}
