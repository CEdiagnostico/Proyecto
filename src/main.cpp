#include<iostream>
#include <pthread.h>
#include "socket.h"
//#include"gui.h"
//#include"terrain.h"
//#include "clasesLogicas.h"

using namespace std;
/** @name Crazy River Ride
*
* @author Roberto Bonilla Jara
* @author Alex Feng Li
* @author Ernesto Ulate
* @author Pablo Rodriguez
*test
* @version 1.0
* @date 2015
*/
int main() {
    //prueba gui
	pthread_t socket;
		pthread_create(&socket, 0, startSocket, 0);
		int i;
		pthread_join(socket,0);
    return 0;
}
