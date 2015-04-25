//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_GAMECREATOR_H
#define PROYECTO_GAMECREATOR_H

#include "Headers/Jugador.h"
#include "Headers/Obstaculo.h"
#include "Headers/Enemigo.h"
#include "Headers/Member.h"
#include "Headers/Constants.h"
#include <iostream>

class GameCreator {
    public:
        void* create();
};


#endif //PROYECTO_GAMECREATOR_H
