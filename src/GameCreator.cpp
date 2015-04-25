//
// Created by roberto on 24/04/15.
//

#include "GameCreator.h"

void* GameCreator::create(){
    void* ret = malloc(sizeof(Member) * 7);
    *static_cast<Jugador*>(ret) = Jugador(1,0,0);
    ((Jugador*)(ret))->changeFlag();
    for(int i=1; i<=3; i++){
        *static_cast<Obstaculo*>(ret+i) = Obstaculo(i+1,0,0);
        *static_cast<Enemigo*>(ret+2*i) = Enemigo(2*i+1,0,0);
    }
    return ret;
};
