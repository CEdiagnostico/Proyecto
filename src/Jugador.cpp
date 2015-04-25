//
// Created by roberto on 24/04/15.
//

#include "Jugador.h"

Jugador::Jugador(int paramId, int paramX, int paramY){
    active = 1;
    x = paramX;
    y = paramY;
    id = paramId;
};

bool Jugador::colisiones(Member* lista){
    for(int i =0; i<7; i++){
        Member* tmp = (Member*)(lista+i*sizeof(Member));
        if(tmp->getFlag() && x==tmp->getX() && 5==tmp->getY()){
            return true;
        }
    }
    return false;
};

void Jugador::bajarCombustible(){
    combustible -= 10;
};

int Jugador::getCombustible(){
    return combustible;
};