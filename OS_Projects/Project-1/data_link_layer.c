#include"encDec.h"

int main(int argc, char *argv[]){ // main class executed when exec is called in application layer
	printf("%s",argv[3]);
	if (strcmp(argv[2],"framing") == 0){
		Framing(argv[1],argv[3]);
	}
	else if (strcmp(argv[2],"deframing") == 0) {
		Deframing(argv[1],argv[3]);
	}
	else {
		return -1;
	} 
	return 1;
}

void Framing(char *data, char *fileName){ // Converts all the input data into frames as mentioned in the project proposaal and used

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
	decision_function(frame,"ctob",fp);//last frame left after all frames filled with 64 characters
	fclose(fp);
		/*for (int p = 3;p<frame[2];p++){
		printf("%c",frame[p]);
		}*/
}

void Deframing(char *data, char *fileName){ //Deeframing the binary daata so ttthat it can be converted intto chhars
	
	long length = strlen(data);
	char frame[67*8];
	long i,j,k=0;
	FILE *fp  = fopen(fileName,"w");

	for (i =0; i < length/(67*8); i++ ){
		strcpy(frame,"");
		k=0;

		for (j = i*(67)*8 ; j < (i+1)*67*8 ; j++ ) {

			frame[k++] = data[j]; 
		}

		decision_function(frame,"btoc",fp);
		
	}
	strcpy(frame,"");
	k=0;
	for (j = j ; j < length ; j++ ) { ///lasssst frame left to be converted 
		frame[k++] = data[j];
	}

	decision_function(frame,"btoc",fp);
	fclose(fp);
	
}
