#include"encDec.h"

void decision_function( char *data, char *function, FILE *fileName){ //Make sure of the file name and function to be invoked 

	if (strcmp(function,"ctob") == 0){

		
		for (int i =0 ; i < strlen(data); i++){
			char_to_binary(data[i], fileName);
		}
	}
	else if (strcmp(function,"btoc") == 0) { // calling btoooc so the binary can be converted to chaar
		char binary[8] = {'\0'};
		for (int i =3; i < strlen(data)/8; i++ ){
			int k=0;

			for (int j = (i*8) ; j < ((i+1)*8) ; j++ ) {
				binary[k++] = data[j]; 

			}
			//printf("\n%s",binary);
			
			binary_to_char(binary,fileName);
			//break;
		}
	}
}


void char_to_binary(char character, FILE *fp){ //conversion of char to binary using bbitwise operators
	char binary[8] = {'\0'};
	int parity_count = 0;
	for (int i = 7; i > 0; i--){
		binary[i]  = ((character << i) & 0b10000000)?'1':'0';
		if(binary[i] == '1') {
			parity_count++;
		}
	}
	binary[0] = parity_count%2 == 0?'1':'0';	//Adding odd parity bit based on the count
	fwrite(binary,sizeof(char),8,fp);

}	

void binary_to_char(char *binary, FILE *fp){
	char result[1] = {'\0'};
	for (int i = 1; i<8;i++){
	result[0] = (result[0] << 1) | (binary[i] - '0'); //conversion of binary strinbg to char using bitwise operators
	}	


	
	result[0]= (result[0]>=97 && result[0]<=122)?result[0]-32:result[0];
	printf("%s",result);
	//fwrite(result,1,2,fp);
	fprintf(fp,"%s",result);
	
}

