//
// Created by roberto on 24/04/15.
//

#include "Jugador.h"

Jugador::Jugador(int paramId, int paramX, int paramY){
    active = static_cast<int*>(malloc(sizeof(int)));
    *active = false;
    x = static_cast<int*>(malloc(sizeof(int)));
    *x = paramX;
    y = static_cast<int*>(malloc(sizeof(int)));
    *y = paramY;
    id = static_cast<int*>(malloc(sizeof(int)));
    *id = paramId;
};

Jugador::~Jugador(){
    free(active);
    free(x);
    free(y);
    free(id);
};
