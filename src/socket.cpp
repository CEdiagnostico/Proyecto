//
// Created by roberto on 24/04/15.
//
#include "socket.h"
#include "Member.h"
#include "Jugador.h"
#include "Updater.h"

#define PORT 9500
#define MAX_BUFFER 1024

using namespace rapidjson;

void* connection_handler(void* param){
    socketThreadParam* info = static_cast<socketThreadParam*>(param);
    int sock = *(info->getSocketDescriptor());
    int read_size;
    char client_message[2000];
    char json2[1024];
    jsonWriter writer = jsonWriter();
    pthread_mutex_lock(&(info->mutex));
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        pthread_cond_wait(&(info->androidCond), &(info->mutex));
        client_message[read_size] = '\0';
        for(int i = 0; i<7; i++){
            Member* tmp = static_cast<Member*>(info->getMembers() + i*sizeof(Member));
                writer.write(i+1, tmp->getFlag(), tmp->getX(), tmp->getY(), json2);
                write(sock , json2, strlen(json2));
        }
        memset(client_message, 0, 2000);
    }
    pthread_mutex_unlock(&(info->mutex));
    if(read_size == 0){
        puts("Client disconnected");
    }else if(read_size == -1) {
        perror("recv failed");
    }

    return 0;
}

void* threadAndroid(void* param) {
    socketThreadParam* info = static_cast<socketThreadParam*>(param);
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    Updater upd;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.0.119");
    server_addr.sin_port = htons(PORT);

    /* bind with the local file */
    bind(server_sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    /* listen */
    listen(server_sockfd, 5);

    int size;
    char buffer[MAX_BUFFER + 1];
    int client_sockfd;
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    /* accept a connection */
    printf("waiting connection...\n");
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &len);
    printf("connection established!\n");

    while(true){
        pthread_mutex_lock(&(info->mutex));
        size = read(client_sockfd, buffer, MAX_BUFFER);
        buffer[size] = '\0';
        std::string a = "";
        std::string b = "";
        bool flag=false;
        for(int i=0; i<size; i++){
            if(buffer[i]==35){
                if(!flag){
                    flag=true;
                }else{
                    break;
                }
            }else if(!flag){
                a+=buffer[i];
            }else{
                b+=buffer[i];
            }
        }
        (static_cast<Jugador*>(info->getMembers()))->setX(atoi(a.c_str()));
        (static_cast<Jugador*>(info->getMembers()))->setY(atoi(b.c_str()));
        upd.actualizarObjetos(info->getMembers());
        pthread_mutex_unlock(&(info->mutex));
        pthread_cond_signal(&(info->androidCond));
        usleep(500);
    }
    close(client_sockfd);
    return 0;
}

void* startSocket(void* p){
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
        printf("Could not create socket");
    }
    puts("Socket created");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(7777);
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0) {
        perror("bind failed. Error");
    }
    listen(socket_desc , 3);
    c = sizeof(struct sockaddr_in);
    pthread_t thread_GUI, thread_Android;

    socketThreadParam* threadParam = static_cast<socketThreadParam*>(malloc(sizeof(socketThreadParam)));
    new(threadParam) socketThreadParam();
    pthread_create(&thread_Android, NULL,  threadAndroid, (void*)threadParam);
    threadParam->setMembers((Member*)p);
    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
    	threadParam->setSocketDescriptor(&client_sock);
    	pthread_create(&thread_GUI, NULL,  connection_handler, (void*)threadParam);
    }
    if (client_sock < 0){
        perror("accept failed");
    }
}
