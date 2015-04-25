//
// Created by roberto on 24/04/15.
//

#include "Enemigo.h"

Enemigo::Enemigo(int paramId, int paramX, int paramY){
    active = static_cast<int*>(malloc(sizeof(int)));
    *active = false;
    x = static_cast<int*>(malloc(sizeof(int)));
    *x = paramX;
    y = static_cast<int*>(malloc(sizeof(int)));
    *y = paramY;
    id = static_cast<int*>(malloc(sizeof(int)));
    *id = paramId;
};

Enemigo::~Enemigo(){
    free(active);
    free(x);
    free(y);
    free(id);
};
