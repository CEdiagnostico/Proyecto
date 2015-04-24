#ifndef ENEMIGO_H
#define ENEMIGO_H

/*
 * Clase Enemigo
 * Tiene argumentos y funciones necesarias para el objeto de Enemigo
 *
 * Existen 3 tipos de enemigos para defnir:
 * 						1 = Nave enemiga basica.
 * 						2 = Nave movil.
 * 						3 = Kamikaze
 */
class Enemigo {

public:
	Enemigo(short int nave, short int identificador); 	//Contructor, se elige el tipo de enemigo
	~Enemigo();             							//Destructor
	short int obtenerVida();							//Obtener la vida actual del enemigo
	void cambiarVida(short int cantidad);				//Disminuye la vida del enemigo al recibir daño
	void cambiarPosicion(int x, int y);					//Cambia la posicion del enemigo por coordenadas
	int getX();											//Obtener la posicion en X del enemigo
	int getY();											//Obtener la posicion en Y del enemigo
	short int tipoNave();								//Obtener el tipo de enemigo (1,2 o 3)
	void disparar();        							//Metodo para hacer funcionar los disparos
private:
	short int calcularVida();    						//Calcula la vida por distribucion gaussiana
	short int *id;										//Atributo de identificacion del enemigo
	short int *tipo;									//Atributo del tipo de nave
	short int *vida;									//Atributo con la cantidad de vida del enemigo
	int *pX;											//Atributo de la coordenada de posicion en X
	int *pY;											//Atributo de la coordenada de posicion en Y

};

#endif // ENEMIGO_H
