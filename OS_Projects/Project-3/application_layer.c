#include"encDec.h"	//Header file created to add all the function prototypes 

int main() {
 	int pipe1[2],pipe2[2];	//Pipe variables
 	char buffer[256];
 	pid_t p,pp,ppp,pppp;	//Multiple Forks
 	long length,nlength,length3;
 	char *data,*ndata, *data3;
 	FILE *fp;
 

 	if(pipe(pipe1) == -1) {	//Pippes creations for data transfer
		printf("Pipe 1 Creation Failed"); 
 	}
 	if (pipe(pipe2) == -1){
 		printf("Pipe 2 Creation Failed");
 	}
 	
 	
 	fp = fopen("input.inpf", "r");  
 	fseek(fp, 0, SEEK_END);		 //Find end of the file 
 	length = ftell(fp);    //find file data length 
 	fseek(fp, 0, SEEK_SET);   //sets the cursor 
 	data = malloc(length + 1);
 	fread(data, length, 1, fp); //read data
 	fclose(fp);
 	
 	//data_linker(data,"framing","input.binf");
	
	
	pp = fork();
 	if(pp<0){
 		printf("Fork Creation Failed");\
 		return 1;
 	}
 	if (pp > 0 ) {
  		int a = execl("data_and_phy","data_and_phy",data,"framing","input.binf",NULL);//EXEC system calll function 
  		if (a == -1){
  		printf("\nEror in EXEC call\n");
  		}
 	} else{
 		wait(NULL);
		FILE *fp1 = fopen("input.binf", "rb");  //Find end of the file 
		fseek(fp1, 0, SEEK_END);		 //find file data length 
		long length1 = ftell(fp1);    //sets the cursor 
		fseek(fp1, 0, SEEK_SET);   //sets the cursor 
		char *data1 = malloc(length1 + 1);
		fread(data1, length1, 1, fp1); //reads data from file
		fclose(fp1);
	
	
 		p = fork();
 		if(p<0){
 			printf("Fork Creation Failed");\
 			return 1;
 		}
 		if (p > 0 ) {
  			
	
			close(pipe1[0]);
			write(pipe1[1], data1, length1+1);
 			close(pipe1[1]);
	
 			printf("Successfullly Wrote into Consumer\n");
		
  			wait(NULL);
  			wait(NULL);
  			close(pipe2[1]);
 			read(pipe2[0],data3,length3);
  			printf("\nSuccessfully Read from consumer");
  			close(pipe2[0]);
  			
 		} else{
 			wait(NULL);
  			close(pipe1[1]);
  			read(pipe1[0],data1,length1+1);
  			//data_linker(data,"framing","input.binf");
  			printf("\n Successfully read from producer");
  			
  			close(pipe1[0]);
  	
  			ppp = fork();
 			if(ppp<0){
 				printf("Fork Creation Failed");\
 				return 1;
 			}
 			if (ppp > 0 ) {
  				int a = execl("data_and_phy","data_and_phy",data1,"deframing","input.outf",NULL);
  				if (a == -1){
  					printf("\nEror in EXEC call\n");
  				}
 			} else{
  				wait(NULL);
  			
  				FILE *fp2 = fopen("input.outf", "r");  //Opens a FILE pointer to read or write on a file
				fseek(fp2, 0, SEEK_END);		 //Finds out the end of the file 
				long length2 = ftell(fp2);    //calculates the file content length 
				fseek(fp2, 0, SEEK_SET);   //sets the cursor 
				char *data2 = malloc(length2 + 1);
				fread(data2, length2, 1, fp2); //reads data from file
				fclose(fp2);
  				
  				pppp = fork();
 				if(pppp<0){
 					printf("Fork Creation Failed");\
 					return 1;
 				}
 				if (pppp > 0 ) {
  					int b = execl("data_and_phy","data_and_phy",data2,"framing","input.chck",NULL);
  					if (b == -1){
  						printf("\nEror in EXEC call\n");
  					}
 				} else{
  					wait(NULL);
  					
  					FILE *fp3 = fopen("input.chck", "rb");  
					fseek(fp3, 0, SEEK_END);		 
					length3 = ftell(fp3);     
					fseek(fp3, 0, SEEK_SET);   //sets the cursor 
					data3 = malloc(length3 + 1);
					fread(data3, length3, 1, fp3); //reads data from file
					fclose(fp3);
  				
					
  					close(pipe2[0]);
  					write(pipe2[1], data3,length3+1);
  					close(pipe2[1]);
  					printf("Data sent from Consumer ");
  					
  					int c = execl("data_and_phy","data_and_phy",data3,"deframing","input.done",NULL);
  				if (c == -1){
  					printf("\nEror in EXEC call\n");
  				}
  		
  					
  }
  
	}
 }
 			
}
}

