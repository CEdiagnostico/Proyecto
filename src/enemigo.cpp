# include "../headers/enemigo.h"
#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
using namespace std;

/**
 * Constructor del objeto Enemigo
 *
 * @param short int nave, establece el tipo de nave enemiga
 * @param short int identificador, establece un numero identificador para el objeto
 */
Enemigo::Enemigo(short int nave, short int identificador) {
	id = (short int*) malloc(sizeof(short int));
	tipo = (short int*) malloc(sizeof(short int));
	vida = (short int*) malloc(sizeof(short int));
	pX = (int*) malloc(sizeof(int));
	pY = (int*) malloc(sizeof(int));
	switch (nave) {
		case 1:
			*id = identificador;		//Asigna el numero de identificacion del objeto.
			*tipo = nave;				//Asigna el valor del tipo de nave.
			*vida = calcularVida();		//Asigna el valor de vida para el objeto.
			break;
		case 2:
			*id = identificador;		//Asigna el numero de identificacion del objeto.
			*tipo = nave;				//Asigna el valor del tipo de nave.
			*vida = calcularVida();		//Asigna el valor de vida para el objeto.
			break;
		case 3:
			*id = identificador;		//Asigna el numero de identificacion del objeto.
			*tipo = nave;				//Asigna el valor del tipo de nave.
			*vida = 1;					//Asigna el valor de vida para el objeto.
			break;
	};
}
;

/**
 * Destructor del objeto Enemigo.
 *
 */
Enemigo::~Enemigo() {
	free(id);
	free(vida);
	free(tipo);
	free(pX);
	free(pY);
}
;

/**
 * Retorna la vida actual del enemigo.
 *
 */
short int Enemigo::obtenerVida() {
	return *vida;
}
;

/**
 * Disminuir la vida del enemigo. Si esta llega a cero, el objeto desaparece.
 *
 * @param short int cantidad, valor de dano causado al enemigo.
 */
void Enemigo::cambiarVida(short int cantidad) {
	*vida = *vida - cantidad;
	if (*vida <= 0)
		this->~Enemigo();
}
;

/**
 * Asigna una posicion en las coordenadas X,Y para el objeto enemigo
 *
 * @param int x, coordenada en el eje x.
 * @param int y, coordenada en el eje y.
 */
void Enemigo::cambiarPosicion(int x, int y) {
	*pX = x;
	*pY = y;
}
;

/**
 * Retorna la posicion en X del objeto actual.
 *
 */
int Enemigo::getX() {
	return *pX;
}
;

/**
 * Retorna la posicion en Y del objeto actual.
 *
 */
int Enemigo::getY() {
	return *pY;
}
;

/**
 * Retorna el valor del tipo de nave del objeto enemigo.
 * Posibles valores a retornar:
 * 						1 = Nave enemiga basica.
 * 						2 = Nave movil.
 * 						3 = Kamikaze
 *
 */
short int Enemigo::tipoNave() {
	return *tipo;
}
;

/**
 * Metodo para que el objeto actual pueda disparar y causar dano.
 *
 */
void Enemigo::disparar() {
}
;

/**
 * Metodo privado. Retorna el calculo de la vida por distribucion gaussiana.
 *
 */
short int Enemigo::calcularVida() {
//	random_device rd;
//	mt19937 gen(rd());
//	normal_distribution<> d(3);
//	int num = d(gen);
	return 5;
}
;
