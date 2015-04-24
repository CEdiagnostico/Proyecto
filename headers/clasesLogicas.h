#include <iostream>
#include <random>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

#ifndef CLASESLOGICAS_H_INCLUDED
#define CLASESLOGICAS_H_INCLUDED

std::default_random_engine generator;    //Motor random

/** @brief Declaracion da la clase jugador
 *
 * Crea el jugador
 */
class Jugador{
    std::string nombre;                  //Nombre del jugador
    unsigned short int *vida;            //valor de la vida
    unsigned short int *combustible;     //valor del combustible
    short int *velocidad;                //valor de la velocidad
    int *municion;                       //cantidad restante de municion [basica 0-40, pro 0-40, difusion 0-40, mayhem 0-40]
    int *pX;                             //posicion del jugador en X
    int *pY;                             //posicion del jugador en Y
    bool *armaCaliente;                  //Bandera para municion basica
    void cambiarCalorDeArma(bool);       //Calienta o enfria el arma

    public:
        Jugador(std::string);                           //Constructor
        ~Jugador();                                     //Destructor
        void modificarVida(int&&);                      //Modifica la vida con un entero
        void modificarVida(int&);                       //Modifica la vida con una referencia
        unsigned short int obtenerVida();               //Retorna la vida
        bool revisarVida();                             //Revisa que la vida sea mayor a 0
        void modificarCombustible(int&);                //Modifica el combustible con una referencia
        unsigned short int obtenerCombustible();        //Retorna el combustible
        bool revisarCombustible();                      //Revisa que el combustible sea mayor a 0
        std::string obtenerNombre();                    //Retorna el nombre del jugador
        void disparar(int);                             //Dispara la municion que la referencia indique
        void cambiarCantidadDeMunicion(int, int);       //Cambia la cantidad de municion
        void cambiarPosicion(int,int);                  //Cambia la posicion del jugador
        int obtenerX();                                 //Devuelve la posicion en X del jugador
        int obtenerY();                                 //Devuelve la posicion en Y del jugador
};

/** @brief Construye al jugador
 *
 * @param string &n, el nombre del jugador
 */
Jugador::Jugador(std::string n){
    nombre=n;                                     //Toma el nombre del parametro

    short unsigned int v=100;
    vida=static_cast<short unsigned int*>(malloc(sizeof(v)));
    *vida=v;                                        //Inicia con la vida completa

    short unsigned int c=100;
    combustible=static_cast<short unsigned int*>(malloc(sizeof(c)));
    *combustible=c;                               //Inicia con el combustible completo

    short int ve=100;
    velocidad=static_cast<short int*>(malloc(sizeof(ve)));
    *velocidad=ve;                                  //Valor de la velocidad

    int m[4]={40,40,40,40};
    municion=static_cast<int*>(malloc(4*sizeof(int)));
    *municion=*m;

    int poX=0;
    pX=static_cast<int*>(malloc(sizeof(int)));
    *pX=poX;

    int poY=0;
    pY=static_cast<int*>(malloc(sizeof(int)));
    *pY=poY;

    bool a=false;
    armaCaliente=static_cast<bool*>(malloc(sizeof(a)));
    *armaCaliente=a;
};

/** @brief Destruye
 *
 */
Jugador::~Jugador(){
    //free(nombre);
    free(vida);
    free(velocidad);
    free(municion);
    free(pX);
    free(pY);
    free(armaCaliente);
    free(combustible);
};

/** @brief Modifica el valor de la vida segun una referencia
 *
 * @param unsigned short int&
 */
void Jugador::modificarVida(int &&a){
    *vida+=a;                                    //Cambia el valor
    if(*vida>100){                               //Revisa que no se pase del maximo
        *vida=100;                               //Si se pasa asigna el valor maximo
    }else if(*vida<=0){                          //Revisa que no este muerto
        std::cout<<nombre<<" ha muerto"<<std::endl;
    };
};

/** @brief Modifica el valor de la vida segun una referencia
 *
 * @param unsigned short int&
 */
void Jugador::modificarVida(int &a){
    *vida+=a;                                    //Cambia el valor
    if(*vida>100){                               //Revisa que no se pase del maximo
        *vida=100;                               //Si se pasa asigna el valor maximo
    }else if(*vida<=0){                          //Revisa que no este muerto
        std::cout<<nombre<<" ha muerto"<<std::endl;
    };
};

/** @brief Devuelve el valor de la vida
 *
 * @return unsigned short int
 */
unsigned short int Jugador::obtenerVida(){
    return *vida;        //Devuelve la vida
 };

/** @brief Revisa que el jugador siga con vida
 *
 * @return bool
 */
bool Jugador::revisarVida(){
    return *vida>0;      //Devuelve true si y solo si el jugador sigue vivo
 };

/** @brief Modifica el valor del combustible segun una referencia
 *
 * @param unsigned short int&
 */
void Jugador::modificarCombustible(int &a){
    *combustible+=a;                 //Aumenta combustible
    if(*combustible>100){            //Revisa que no se pase del maximo
        *combustible=100;            //Si se pasa asigna el maximo
    }else if(*combustible<=0){       //Revisa que tenga combustible
        std::cout<< nombre << " no tiene combustible" <<std::endl;
    };
};

/** @brief Devuelve el valor del combustible
 *
 * @return unsigned short int
 */
unsigned short int Jugador::obtenerCombustible(){
    return *combustible;         //Devuelve el combustible
 };

/** @brief Revisa que el jugador siga con combustible
 *
 * @return bool
 */
bool Jugador::revisarCombustible(){
    return *combustible>0;       //Devuelve true si tiene combustible
 };

/** @brief Retorna el nombre del jugador
 *
 * @return string
 */
std::string Jugador::obtenerNombre(){
    return nombre;              //Devuelve el nombre
 };

/** @brief Dispara un tipo de municion
 *
 * @param char &tipo, referencia sobre el tipo de municion para restar la posicion correspondiente en el arreglo
 * @ref 0: Municion Basica
 *      1: Municion Pro
 *      2: Municion de Difusion
 *      3: Municion Mayhem
 */
void Jugador::disparar(int tipo){
    switch(tipo){
        case 0:                                          //Municion basica
            if(municion[0]>0 && !*armaCaliente){          //Revisa que haya municion y el arma este fria
                municion[0]-=1;                          //Resta la municion
                std::cout<<nombre<<" disparo un tiro basico, "<<
                "municion restante: "<<municion[0]<<std::endl;
            }else{
                std::cout<<"No dispone de municion basica"<<
                "o el arma esta caliente"<<std::endl;
            };
            break;

        case 1:                                           //Municion pro
            if(municion[1]>0){                            //Revisa que haya municion
                municion[1]-=1;                           //Resta la municion
                std::cout<<nombre<<" disparo un tiro pro, "<<
                "municion restante: "<<municion[1]<<std::endl;
            }else{
                std::cout<< "No dispone de municion pro" <<std::endl;
            };
            break;

        case 2:                                          //Municion de difusion
            if(municion[2]>4){                           //Revisa que haya municion
                municion[2]-=5;                          //Resta la municion
                std::cout<<nombre<<" disparo un tiro difusion, "<<
                "municion restante: "<<municion[2]<<std::endl;
            }else{
                std::cout<<"No dispone de municion de difusion"<<std::endl;
            };
            break;

        case 3:                                          //Municion mayhem
            if(municion[3]>0){                           //Revisa que haya municion
                municion[3]-=1;                          //Resta la municion
                std::cout<<nombre<<" disparo un tiro mayhem, "<<
                "municion restante: "<<municion[3]<<std::endl;
            }else{
                std::cout<<"No dispone de municion mayhem"<<std::endl;
            };
            break;

        default:                                        //Error
            std::cout<< "Error, tipo de municion invalida";
            break;
    };
 };

/** @brief Cambia calor del arma
 *
 * @param bool cambio, true: caliente - false: fria
 */
void Jugador::cambiarCalorDeArma(bool cambio){
    *armaCaliente=cambio;              //Devuelve el nombre
 };

/** @brief Cambia la cantidad la municion de determinado tipo
 *
 * @param int tipo, es el tipo de municion
 * @param int cantidad, es la cantidad de variacion
 */
void Jugador::cambiarCantidadDeMunicion(int tipo, int cantidad){
    if((municion[tipo]+cantidad)<40  &&  (municion[tipo]+cantidad)>0){      //Revisa que el resultado este entre 0 y 40
       municion[tipo]+=cantidad;
    }else if(cantidad>0){     //Si la cantidad es positiva y la operacion resulto fuera de rango, es porque supera los 40
        municion[tipo]=40;
    }else{
        municion[tipo]=0;     //Si la cantidad es negativa y la operacion resulto fuera de rango, es porque es menor que 0
    };
 };

/** @brief Cambia la cantidad la posicion del jugador
 *
 * @param int x
 * @param int y
 */
 void Jugador::cambiarPosicion(int x, int y){
    *pX=x;
    *pY=y;
 };

/** @brief Devuelve posicion en X
 *
 * @return int
 */
 int Jugador::obtenerX(){
    return *pX;
 };

/** @brief Devuelve posicion en Y
 *
 * @return int
 */
 int Jugador::obtenerY(){
    return *pY;
 };






/**  MUNICION  **/
/**************************************************************************************************************************
**************************************************************************************************************************/





/** @brief Declaracion da la clase Municion
 *
 * Esta clase tomara identidad con base en un entero, serivira para representar, de manera logica,
 * la municion que aparecera en el camino.
 * Servira para tomar desiciones estrictamente logicas cuando un usuario colisione o dispare a la
 * representacion grafica del mismo
 * De la misma manera, el uso de un entero como identidad facilitara el manejo del random
 *
 * @ref 0: Municion basica
 *      1: Municion pro
 *      2: Municion de difusion
 *      3: Municion mayhem
 */
class Municion{
    int tipo;                           //Tipo de objeto

    public:
        Municion(int);                  //Constructor
        ~Municion();                    //Destructor
        void colision(Jugador*);        //Colision con el jugador

};

/** @brief Construye el objeto segun parametro
 *
 * @param int t, el tipo
 */
Municion::Municion(int t){
    tipo=t;
};

/** @brief Destruye
 *
 */
Municion::~Municion(){};


void Municion::colision(Jugador *j){
    j->cambiarCantidadDeMunicion(tipo,rand()%10+1);
};






/**  PUENTE  **/
/**************************************************************************************************************************
**************************************************************************************************************************/





/** @brief Declaracion da la clase puente
 *
 * Sera el puente que se ubicara en el rio
 */
class Puente{
    unsigned short int vida;            //valor de la vida

    public:
        Puente(int);                                //Constructor
        ~Puente();                                  //Destructor
        void modificarVida(int&);                   //Modifica la vida con una referencia
        unsigned short int obtenerVida();           //Retorna la vida
        bool revisarVida();                         //Revisa que la vida sea mayor a 0
};

/** @brief Construye el puente
 *
 * @param int v, la vida del puente
 */
Puente::Puente(int v){
    vida=v;           //Inicia con la vida completa
};

/** @brief Destruye
 *
 */
Puente::~Puente(){};

/** @brief Modifica la vida con base en un parametro
 *
 * @param int n, valor de incremento o decremento
 */
void Puente::modificarVida(int &n){
    vida+=n;           //Suma el valor, si es negativo sera igual a una resta
};

/** @brief Devuelve el valor de la vida del puente
 *
 */
unsigned short int Puente::obtenerVida(){
    return vida;           //Retorna la vida
};

/** @brief Revisa si el puente sigue vivo
 *
 * @return bool
 */
bool Puente::revisarVida(){
    return vida>0;           //Retorna true si la vida es mayor a 0, de lo contrario retorna false
};






/**  VIDA  **/
/**************************************************************************************************************************
**************************************************************************************************************************/





/** @brief Declaracion da la clase vida
 *
 * Saldran a lo largo del juego y le daran vida al jugador. Despues de cierto tiempo se vuelve toxica.
 */
 class Vida{
    bool toxicidad;                     //Bandera para decidir efecto
    int valor;                          //Valor de la vida
    public:
        Vida();                         //Contructor
        ~Vida();                        //Destructor
        bool esToxica();                //Metodo para obtener estado de toxicidad
        void cambiarToxicidad(bool);    //Metodo para cambiar estado de toxicidad
        void colision(Jugador*);        //Metodo que se utilizara cuando en el plano grafico un jugador impacte la vida
        void recibirBalazo();           //Metodo que se utilizara cuando en el plano grafico un jugador dispare a la vida
 };

/** @brief Constructor
 *
 * Construye la vida
 */
Vida::Vida(){
    toxicidad=false;
};

/** @brief Destructor
 *
 * Destruye la vida
 */
Vida::~Vida(){};

/** @brief Informa sobre el estado de toxicidad
 *
 * @return bool
 */
bool Vida::esToxica(){
    return toxicidad;
};

/** @brief Cambia la toxicidad segun un parametro
 *
 * @param bool t, nuevo estado de toxicidad
 */
void  Vida::cambiarToxicidad(bool t){
    toxicidad=t;
};

/** @brief Realiza los ajustes logicos cuando un jugador colisiona con la vida
 *
 * @param Jugador *j, jugador que colisiono
 */
void Vida::colision(Jugador *j){
    if(!toxicidad){
        j->modificarVida(valor);
    }else{
        j->modificarVida(-5);
    };
};

/** @brief Realiza los ajustes logicos cuando un jugador dispara a la vida
 *
 */
void Vida::recibirBalazo(){};





/**  TANQUE DE COMBUSTIBLE  **/
/**************************************************************************************************************************
**************************************************************************************************************************/





/** @brief Declaracion da la clase puente
 *
 * Sera el puente que se ubicara en el rio
 */
 class TanqueCombustible{

 };


#endif // CLASESLOGICAS_H_INCLUDED
