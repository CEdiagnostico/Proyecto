//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_SOCKET_H
#define PROYECTO_SOCKET_H

#include <iostream>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include "../../libs/rapidjson/rapidjson.h"
#include "../../libs/rapidjson/document.h"
#include "../../libs/rapidjson/stringbuffer.h"
#include "../../libs/rapidjson/writer.h"
#include "jsonWriter.h"
#include "socketThreadParam.h"
#include "Member.h"
#include "Jugador.h"
#include "Updater.h"
#include "socketThreadParam.h"
#include "GameCreator.h"
#include "Constants.h"

void* playerHandler(void* param);
void* objectHandler(void* param);
void* threadAndroid(void* param);
void* startSocket(void* p);

#endif //PROYECTO_SOCKET_H
