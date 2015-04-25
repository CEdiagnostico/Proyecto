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

int* socketThreadParam::getSocketDescriptor(){
    return socketDesc;
}

pthread_mutex_t socketThreadParam::getMutex(){
    return mutex;
}

pthread_cond_t socketThreadParam::getAndroidCond(){
    return androidCond;
}

void socketThreadParam::setMembers(Members* param){
    members = param;
};

Members* socketThreadParam::getMembers(){
    return members;
};