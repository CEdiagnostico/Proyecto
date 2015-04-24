#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

#include"estructurasDeDatos.h"
//ID de objetos
enum ID{PLAYER, BULLET, ENEMY, BONUS};
enum ID_BONUS{HEALTH,ARMOR};

//El jugador
struct Plane
{
	int ID;
	int x;
	int y;
	int speed;
	bool isDying = false;
	bool death = false;
};
//Enemigo
struct Enemy
{
	int ID;
	int x;
	int y;
	int speed;
	bool isDying = false;
	bool death = false;
};
//Bala
struct Bullet
{
	int ID;
	int x;
	int y;
	int speed;
	bool death = false;
};
//Bonus
struct Bonus
{
	int ID;
	int x;
	int y;
	bool death = false;
};
//Piso
struct Floor
{
	int inicio;//inicia agua
	int fin;//termina agua
	bool puente;
};
#endif
