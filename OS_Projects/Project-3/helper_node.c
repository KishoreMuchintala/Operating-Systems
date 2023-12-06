#include"encDec.h"

sem_t mutex0,mutex1,mutex3,mutex4,mutex5,mutex6,m1,mutex7;
char buffer[5]; //buffer to handle data 
char* inp;
int count = 0;
long length, length1;
FILE* optr;
void *charA_thread(void *vargp) // function will convert char a to A
{ 
const int iter = (strlen(inp)/5)+1;
int count =0;
for(int i=0;i<length;i++){     
    if(inp[i]=='a'){
        inp[i] = 'A';
        }
}
       sem_post(&mutex1);
       sem_wait(&m1);
       
     }

void *charE_thread(void *vargp) //function will convert char e to E by threads 
{   
const int iter = (strlen(inp)/5)+1;  
      sem_wait(&mutex1);
      for(int j=0;j<length;j++){
        if(inp[j]=='e'){
        inp[j] = 'E';
        }
      }
      sem_post(&mutex3);
}
void *charI_thread(void *vargp)//function will convert char i to I by threads 
{
const int iter = (strlen(inp)/5)+1;  
	sem_wait(&mutex3);
	for(int j=0;j<length;j++){
        if(inp[j]=='i'){
        inp[j] = 'I';
        }
        }
	sem_post(&mutex4);
	
}
void *charO_thread(void *vargp)//function will convert char o to O by threads 
{
const int iter = (strlen(inp)/5)+1;  
	sem_wait(&mutex4);
	for(int j=0;j<length;j++){
        if(inp[j]=='o'){
        inp[j] = 'O';
        }
        }
	sem_post(&mutex5);
}
void *charU_thread(void *vargp)//function will convert char u to U by threads 
{const int iter = (strlen(inp)/5)+1;  
	sem_wait(&mutex5);
	for(int j=0;j<length;j++){
        if(inp[j]=='u'){
        inp[j] = 'U';
        }
        }
	
	sem_post(&mutex6);
}

void *concatResult(void *vargp){ // THis helps in moving the threads back to helper functions and return value
sem_post(&m1);

}

char *helper_node(char *data, int len ) // FUnction will help in creating all the required threads and execute one after other.
{
    FILE *fp,*fo;
    
	sem_init(&mutex0, 0, 0);
	sem_init(&mutex1, 0, 0);
	sem_init(&mutex3, 0, 0);
	sem_init(&mutex4, 0, 0);
	sem_init(&mutex5, 0, 0);
	sem_init(&mutex6, 0, 0);
	sem_init(&m1, 0, 0);
    
 	length = len;
 	inp = data;


	pthread_t charA_id;
	pthread_t charE_id;
	pthread_t charI_id;
	pthread_t charO_id;
	pthread_t charU_id;
	pthread_t charNum_id;
	pthread_t concatResult_id;
	pthread_create(&charA_id, NULL, charA_thread, (void*) inp);
	pthread_create(&charE_id, NULL, charE_thread, NULL);
	pthread_create(&charI_id, NULL, charI_thread, NULL);
	pthread_create(&charO_id, NULL, charO_thread, NULL);
	pthread_create(&charU_id, NULL, charU_thread, NULL);
	pthread_create(&concatResult_id, NULL, concatResult, NULL);
	pthread_join(charA_id, NULL);
	pthread_join(charE_id, NULL);
	pthread_join(charI_id,NULL);
	pthread_join(charO_id, NULL);
	pthread_join(charU_id, NULL);
	pthread_join(charNum_id, NULL);
	pthread_join(concatResult_id, NULL);

	sem_destroy(&mutex0);// below commands or methods will destroy all the created threads.
	sem_destroy(&mutex1);
	sem_destroy(&mutex3);
	sem_destroy(&mutex4);
	sem_destroy(&mutex5);
	sem_destroy(&mutex6);
	sem_destroy(&m1);
    
    printf("\n%s\n",inp);
	datachar = inp;
    return inp;
}



