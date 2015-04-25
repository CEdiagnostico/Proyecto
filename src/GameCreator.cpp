//
// Created by roberto on 24/04/15.
//

#include "GameCreator.h"

static void* GameCreator::create(){
    void* ret = malloc(sizeof(Member) * 7);
    new((Jugador*) ret) Jugador(1,0,0);
    ((Jugador*)(ret))->changeFlag();
    for(int i=1; i<=3; i++){
        new((Obstaculo*) ret+i) Obstaculo(i+1,0,0);
        new((Enemigo*) ret+2*i) Enemigo(2*i+1,0,0);
    }
    return ret;
};