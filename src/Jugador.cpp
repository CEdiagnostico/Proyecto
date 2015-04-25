//
// Created by roberto on 24/04/15.
//

#include "Jugador.h"

Jugador(int paramId, int paramX, int paramY){
    super(0,paramId,paramX,paramY);
};

~Jugador(){
    ~Member();
};