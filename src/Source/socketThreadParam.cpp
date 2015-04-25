//
// Created by roberto on 24/04/15.
//

#include "../Headers/socketThreadParam.h"

socketThreadParam::socketThreadParam(){
    socketDesc=0;
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

void socketThreadParam::setMembers(Member* param){
    members = param;
};

Member* socketThreadParam::getMembers(){
    return members;
};
