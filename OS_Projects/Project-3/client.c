#include"encDec.h"
#include"helper_node.c"
int flag =0;
char *dat;
void * doRecieving(void * sockID){ //helps in fetching all the data from server based on the client socketid

	int clientSocket = *((int *) sockID);
	while(1){
		
		char data[1024];
		int read = recv(clientSocket,data,1024,0);
		if(data[0]=='*'){
		printf("Here i am in client for socket 1\n");
		
		datachar = helper_node(data,strlen(data));
		printf("%s\n",datachar);
		if(flag==1){		// send the converted vowels consisting data back to server 
		send(clientSocket,dat,1024,0);
		flag =0;
		}
		}else{
		printf("%s\n",data);
}
}
}

int main(){

	int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8088); //change the port here to execute the code if in case the ./server execution fails
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

	printf("Connection established ............\n");

	pthread_t thread;
	pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

	while(1){
		

		char input[1024];
	
		scanf("%s",input);
		if(strcmp(input,"LOGIN_LIST") == 0){

			send(clientSocket,input,1024,0);

		}
		if(strcmp(input,"MSG") == 0){

			send(clientSocket,input,1024,0);
			
			scanf("%s",input);

			send(clientSocket,input,1024,0);
			
			scanf("%[^\n]s",input);
			send(clientSocket,input,1024,0);

		}
		
		
	}


}
