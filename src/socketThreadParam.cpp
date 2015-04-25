//
// Created by roberto on 24/04/15.
//

#include "socketThreadParam.h"

socketThreadParam::socketThreadParam(){
    socketDesc=0;
    pos=0;
    speed=0;
    androidCond = PTHREAD_COND_INITIALIZER;
    mutex = PTHREAD_MUTEX_INITIALIZER;

}

void socketThreadParam::setSocketDescriptor(int* param){
    socketDesc = param;
}

void socketThreadParam::setPos(int param){
    pos = param;
}

void socketThreadParam::setSpeed(int param){
    speed = param;
}

int* socketThreadParam::getSocketDescriptor(){
    return socketDesc;
}

int socketThreadParam::getPos(){
    return pos;
}

int socketThreadParam::getSpeed(){
    return speed;
}

pthread_mutex_t socketThreadParam::getMutex(){
    return mutex;
}

pthread_cond_t socketThreadParam::getAndroidCond(){
    return androidCond;
}
