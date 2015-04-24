//
// Created by roberto on 24/04/15.
//

#include "socket.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include "../libs/rapidjson/rapidjson.h"
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"
#include "jsonWriter.h"

void *connection_handler(void *socket_desc){
    int sock = *static_cast<int*>(socket_desc);
    int read_size;
    char client_message[2000];
    jsonWriter writer = jsonWriter();
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        client_message[read_size] = '\0';
        write(sock , writer.write(0,0,0,0), strlen(json2));
        memset(client_message, 0, 2000);
        usleep(5000);
    }

    if(read_size == 0){
        puts("Client disconnected");
    }else if(read_size == -1) {
        perror("recv failed");
    }

    return 0;
};

void* startSocket(void*){
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(7777);

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");

    }
    //puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection

    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        //puts("Connection accepted");

        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        {
            //  perror("could not create thread");

        }

        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        // puts("Handler assigned");
    }

    if (client_sock < 0)
    {
        perror("accept failed");

    }
};