#include"terrain.h"

using namespace std;




TerrainGenerator::TerrainGenerator()
{
    std::srand(6);// define seed
    ultimoTerreno.inicio = 40;
    ultimoTerreno.fin = WIDTH-40;
    ultimoTerreno.puente = false;
}
Floor TerrainGenerator::obtenerTerreno()
{
    //pointers
    int* left = &(ultimoTerreno.inicio);
    int* right = &(ultimoTerreno.fin);


    int leftStep = -1 + (std::rand() % (int)(3));
    int rightStep = -1 + (std::rand() % (int)(3));
    int puente = (std::rand() % (int)(15));
    ultimoTerreno.puente = (!puente);

    *left = *left + leftStep*PIXEL;
    *right = *right + rightStep*PIXEL;

    if (*left< LEFT_BOUND_LEFT) *left = LEFT_BOUND_LEFT;
    if (*right< RIGHT_BOUND_LEFT) *right = RIGHT_BOUND_LEFT;
    if (*left> LEFT_BOUND_RIGHT) *left = LEFT_BOUND_RIGHT;
    if (*right> RIGHT_BOUND_RIGHT) *right = RIGHT_BOUND_RIGHT;

    return ultimoTerreno;
}
