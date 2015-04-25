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

void* playerHandler(void* param){
    socketThreadParam* info = static_cast<socketThreadParam*>(param);
    int sock = *(info->getSocketDescriptor());
    int read_size;
    char client_message[2000];
    char json2[1024];
    jsonWriter writer = jsonWriter();
    Member* player = static_cast<Jugador*>(info->getMembers());
    pthread_mutex_lock(&(info->mutex));
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        pthread_cond_wait(&(info->androidCond), &(info->mutex));
        client_message[read_size] = '\0';
        writer.write(1, player->getFlag(), player->getX(), player->getY(), json2);
        write(sock , json2, strlen(json2));
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

void* objectHandler(void* param){
    socketThreadParam* info = static_cast<socketThreadParam*>(param);
    int sock = *(info->getSocketDescriptor());
    int read_size;
    char client_message[2000];
    char json2[1024];
    jsonWriter writer = jsonWriter();
    Updater upd;
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        client_message[read_size] = '\0';
        for(int i = 1; i<7; i++){
            Member* tmp = static_cast<Member*>(info->getMembers() + i*sizeof(Member));
            writer.write(i+1, tmp->getFlag(), tmp->getX(), tmp->getY(), json2);
            write(sock , json2, strlen(json2));
            usleep(100000);
        }
        memset(client_message, 0, 2000);
        upd.actualizarObjetos(info->getMembers());
    }
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
        pthread_mutex_unlock(&(info->mutex));
        pthread_cond_signal(&(info->androidCond));
    }
    close(client_sockfd);
    return 0;
}

void* startSocket(void* p){
    int playerSocket_desc , playerClient_sock , c, objectSocket_desc , objectClient_sock;
    struct sockaddr_in server1 , client1, server2, client2;
    playerSocket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (playerSocket_desc == -1){
        printf("Could not create socket");
    }
    objectSocket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (objectSocket_desc == -1){
        printf("Could not create socket");
    }
    puts("Sockets created");
    server1.sin_family = AF_INET;
    server1.sin_addr.s_addr = INADDR_ANY;
    server1.sin_port = htons(7777);
    server2.sin_family = AF_INET;
    server2.sin_addr.s_addr = INADDR_ANY;
    server2.sin_port = htons(7778);
    if( bind(playerSocket_desc,(struct sockaddr *)&server1 , sizeof(server1)) < 0) {
        perror("bind failed. Error");
    }
    if( bind(objectSocket_desc,(struct sockaddr *)&server2 , sizeof(server2)) < 0) {
        perror("bind failed. Error");
    }
    listen(playerSocket_desc , 3);
    listen(objectSocket_desc , 3);
    c = sizeof(struct sockaddr_in);
    
    pthread_t thread_Player, thread_Android, thread_Objects;
    socketThreadParam* threadParam1 = static_cast<socketThreadParam*>(malloc(sizeof(socketThreadParam)));
    socketThreadParam* threadParam2 = static_cast<socketThreadParam*>(malloc(sizeof(socketThreadParam)));
    new(threadParam1) socketThreadParam();
    new(threadParam2) socketThreadParam();
    pthread_create(&thread_Android, NULL,  threadAndroid, (void*)threadParam1);
    threadParam1->setMembers((Member*)p);
    threadParam2->setMembers((Member*)p);
    
    while( (playerClient_sock = accept(playerSocket_desc, (struct sockaddr *)&client1, (socklen_t*)&c)) 
            && (objectClient_sock = accept(objectSocket_desc, (struct sockaddr *)&client2, (socklen_t*)&c))){
    	threadParam1->setSocketDescriptor(&playerClient_sock);
    	pthread_create(&thread_Player, NULL,  playerHandler, (void*)threadParam1);
        threadParam2->setSocketDescriptor(&objectClient_sock);
        pthread_create(&thread_Objects, NULL, playerHandler, (void*)threadParam2);
    }
    if (playerClient_sock < 0){
        perror("accept failed");
    }
}
