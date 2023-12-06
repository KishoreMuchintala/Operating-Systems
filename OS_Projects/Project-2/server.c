#include"encDec.h"

int clientCount = 0;

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client {
    int index;
    char name[8];
    int sockID;
    struct sockaddr_in clientAddr;
    socklen_t len;  // Change the type to socklen_t
};

struct client Client[1024];
pthread_t thread[1024];
void *doNetworking(void *ClientDetail) {
    struct client *clientDetail = (struct client *)ClientDetail;
    int index = clientDetail->index;
    int clientSocket = clientDetail->sockID;
    FILE *fp,*fo;
    printf("Client %d connected.\n", index + 1);

    while (1) {
        char data[1024] = {'\0'};
        int read = recv(clientSocket, data, 1024, 0);
        
        char output[1024];

        if (strcmp(data, "LOGIN_LIST") == 0) {
            int l = 0;
            for (int i = 0; i < clientCount; i++) {
                if (i != index)
                    l += snprintf(output + l, 1024, "Client %d is at socket %d.\n", i + 1, Client[i].sockID);
            }

            send(clientSocket, output, 1024, 0);
            

        }
        if (strcmp(data, "MSG") == 0) {
            read = recv(clientSocket, data, 1024, 0);

            int id = atoi(data) - 1;
            
            read = recv(clientSocket, data, 1024, 0);
            printf("\n%s\n",data);
            int clientid ;
            for (int k =0;k< clientCount;k++){
                if(Client[k].sockID == clientSocket){
                    clientid = k;
                    break;
                }
            }
            clientid++;
            char buffer[1000]; // The filename buffer.
            // Put "file" then k then ".txt" in to filename.
            snprintf(buffer, sizeof(char) * 1000, "C%iC%i.txt",clientid,Client[id].index);
            fp = fopen(buffer,"a");
            snprintf(buffer, sizeof(char) * 1000,   "Message from client %d : %s ",clientid,data);
            fwrite (buffer, 1, strlen(buffer) , fp);
            fclose(fp);
            send(Client[id].sockID, (buffer), 1024, 0);
        }
        if (strcmp(data, "LOGIN") == 0){

        }
    }

    return NULL;
}

int main() {
    int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8050);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
        return 0;

    if (listen(serverSocket, 1024) == -1)
        return 0;

    printf("Server started listening on port 8080 ...........\n");

    while (1) {
        Client[clientCount].sockID = accept(serverSocket, (struct sockaddr *)&Client[clientCount].clientAddr, &Client[clientCount].len);
        Client[clientCount].index = clientCount;
        pthread_create(&thread[clientCount], NULL, doNetworking, (void *)&Client[clientCount]);

        clientCount++;
    }

    for (int i = 0; i < clientCount; i++)
        pthread_join(thread[i], NULL);

    return 0;
}
