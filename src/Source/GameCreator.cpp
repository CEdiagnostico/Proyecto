//
// Created by roberto on 24/04/15.
//

#include "Headers/GameCreator.h"

void* GameCreator::create(){
    void* ret = malloc(sizeof(Member) * NUMBER_OF_MEMBERS);
    *static_cast<Jugador*>(ret) = Jugador(1,0,0);
    std::cout << static_cast<Jugador*>(ret)->getCombustible() << std::endl;
    for(int i=1; i<4; i++) {
        *static_cast<Obstaculo*>(ret+i*sizeof(Obstaculo)) = Obstaculo(i,0,0);
        *static_cast<Enemigo*>(ret+(i+3)*sizeof(Enemigo)) = Enemigo(i+3,0,0);
    }
    *static_cast<Bala*>(ret+7*sizeof(Member)) = Bala(8,0,0);
    return ret;
};
