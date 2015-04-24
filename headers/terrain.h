#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include "estructurasDeDatos.h"
#include"constants.h"
#include"objects.h"

class TerrainGenerator
{

    private:
        const int HALF = WIDTH/2;
        const int START_LEFT = 60;
        const int START_RIGHT =  WIDTH-60;
        const int LEFT_BOUND_LEFT = 20;
        const int LEFT_BOUND_RIGHT = HALF - 20;
        const int RIGHT_BOUND_LEFT = HALF + 20;
        const int RIGHT_BOUND_RIGHT = WIDTH -20;
        Floor ultimoTerreno;
    public:
        TerrainGenerator();
        Floor obtenerTerreno();
};

#endif // TERRAIN_H_INCLUDED
