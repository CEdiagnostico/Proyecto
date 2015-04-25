//
// Created by roberto on 25/04/15.
//

#include "Headers/Bala.h"

Bala::Bala(int paramId, int paramX, int paramY){
    active = 1;
    x = paramX;
    y = paramY;
    id = paramId;
    combustible = 100;
    disparando = false;
};

Member* Bala::colisiones(Member* lista){
    for(int i =0; i<7; i++){
        Member* tmp = (Member*)(lista+i*sizeof(Member));
        if(tmp->getFlag() && x==tmp->getX() && y==tmp->getY()){
            return tmp;
        }
    }
    return 0;
};