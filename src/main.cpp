#include<iostream>
#include <pthread.h>
#include "socket.h"
#include "GameCreator.h"

using namespace std;
/** @name Crazy River Ride
*
* @author Roberto Bonilla Jara
* @author Ernesto Ulate
* @version 1.0
* @date 2015
*/
int main() {
    pthread_t socket;
    pthread_create(&socket, 0, startSocket, GameCreator::create());
    pthread_join(socket,0);
    return 0;
}
