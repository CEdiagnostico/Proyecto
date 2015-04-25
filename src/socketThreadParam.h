//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_SOCKETTHREADPARAM_H
#define PROYECTO_SOCKETTHREADPARAM_H

#include <pthread.h>
#include <cstdlib>

class socketThreadParam {
	int* socketDesc;
	Member* members;
	public:
	pthread_mutex_t mutex;
	pthread_cond_t androidCond;
	socketThreadParam();
	void setSocketDescriptor(int*);
	void setMembers(Members*);
	Members* getMembers();
	int* getSocketDescriptor();
	pthread_mutex_t getMutex();
	pthread_cond_t getAndroidCond();
};

#endif //PROYECTO_SOCKETTHREADPARAM_H
