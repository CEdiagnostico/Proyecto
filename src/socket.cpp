//
// Created by roberto on 24/04/15.
//
#include "socket.h"
#include "Member.h"
#include "Jugador.h"
#include "Updater.h"

#define PORT_ANDROID 9500
#define MAX_BUFFER 1024
#define NUMBER_OF_MEMBERS 7
#define PORT_PLAYER 7777
#define PORT_OBJECTS 7778

using namespace rapidjson;

void* playerHandler(void* param){
    socketThreadParam* info = static_cast<socketThreadParam*>(param);
    int sock = *(info->getSocketDescriptor());
    int read_size;
    char client_message[2000];
    char json2[MAX_BUFFER];
    jsonWriter writer = jsonWriter();
    Jugador* player = static_cast<Jugador*>(info->getMembers());
    int cnt = 0;
    bool flag = true;
    while( flag && (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        pthread_cond_wait(&(info->androidCond), &(info->mutex));
        client_message[read_size] = '\0';
        if(cnt==10){
            player->bajarCombustible();
            cnt=0;
        }
        writer.write(1, player->getFlag(), player->getX(), player->getCombustible(), json2);
        write(sock , json2, strlen(json2));
        memset(client_message, 0, 2000);
        cnt++;
        if(player->getCombustible()<=0) {
            flag=false;
        }
    }
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
    char json2[MAX_BUFFER];
    jsonWriter writer = jsonWriter();
    Updater upd;
    int sleep = 10000;
    int cnt =0;
    bool flag = true;
    while( flag && (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        client_message[read_size] = '\0';
        for(int i = 1; i<NUMBER_OF_MEMBERS; i++){
            Member* tmp = static_cast<Member*>(info->getMembers() + i*sizeof(Member));
            writer.write(i+1, tmp->getFlag(), tmp->getX(), tmp->getY(), json2);
            write(sock , json2, strlen(json2));
            usleep(sleep);
        }
        if(cnt==10 && sleep>=1000){
            sleep -= 100;
            cnt=0;
        }
        if(static_cast<Jugador*>(info->getMembers())->getCombustible()<=0){
            flag=false;
        }
        memset(client_message, 0, 2000);
        upd.actualizarObjetos(info->getMembers());
        cnt++;
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
    server_addr.sin_port = htons(PORT_ANDROID);

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
    bool cnd = true;
    while(cnd){
        pthread_mutex_lock(&(info->mutex));
        size = read(client_sockfd, buffer, MAX_BUFFER);
        buffer[size] = '\0';
        std::string a = "";
        bool flag=false;
        for(int i=0; i<size; i++){
            if(buffer[i]==35){
                    break;
            }else{
                a+=buffer[i];
            }
        }
        Jugador* j = static_cast<Jugador*>(info->getMembers());
        if(j->getCombustible<=0){
            cnt=false;
        }else if(j->colisiones(info->getMembers())){
            j->changeFlag();
        }else{
            int nPos = atoi(a.c_str());
            if(nPos<0){
                if(j->getX() < 3){
                    nPos = j->getX() + 1;
                }else{
                    nPos=3;
                }
            }else{
                if(j->getX() > 1){
                    nPos = j->getX() - 1;
                }else{
                    nPos=1;
                }
            }
            j->setX(nPos);
        }
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
    server1.sin_port = htons(PORT_PLAYER);
    server2.sin_family = AF_INET;
    server2.sin_addr.s_addr = INADDR_ANY;
    server2.sin_port = htons(PORT_OBJECTS);
    if( bind(playerSocket_desc,(struct sockaddr *)&server1 , sizeof(server1)) < 0) {
        perror("bind failed. Error");
    }
    if( bind(objectSocket_desc,(struct sockaddr *)&server2 , sizeof(server2)) < 0) {
        perror("bind failed. Error");
    }
    listen(playerSocket_desc , 3);
    listen(objectSocket_desc , 4);
    c = sizeof(struct sockaddr_in);
    
    pthread_t thread_Player, thread_Android, thread_Objects;
    socketThreadParam1* threadParam = static_cast<socketThreadParam*>(malloc(sizeof(socketThreadParam)));
    new(threadParam1) socketThreadParam();
    socketThreadParam2* threadParam = static_cast<socketThreadParam*>(malloc(sizeof(socketThreadParam)));
    new(threadParam2) socketThreadParam();
    pthread_create(&thread_Android, NULL,  threadAndroid, (void*)threadParam1);
    threadParam1->setMembers((Member*)p);
    threadParam2->setMembers((Member*)p);
    
    while( (playerClient_sock = accept(playerSocket_desc, (struct sockaddr *)&client1, (socklen_t*)&c)) 
            && (objectClient_sock = accept(objectSocket_desc, (struct sockaddr *)&client2, (socklen_t*)&c))){
    	threadParam1->setSocketDescriptor(&playerClient_sock);
        threadParam2->setSocketDescriptor(&objectClient_sock);
    	pthread_create(&thread_Player, NULL,  playerHandler, (void*)threadParam1);
        pthread_create(&thread_Objects, NULL, objectHandler, (void*)threadParam2);
    }
    if (playerClient_sock < 0){
        perror("accept failed");
    }
}
