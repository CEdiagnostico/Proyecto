//
// Created by roberto on 24/04/15.
//

#include "../Headers/Member.h"

void Member::setX(int newX){
    x=newX;
}
void Member::setY(int newY){
    y=newY;
}
void Member::changeFlag(){
    if(active==0){
    	active=1;
    }else{
    	active=0;
    }
}
int Member::getX(){
    return x;
}
int Member::getY(){
    return y;
}
int Member::getId(){
    return id;
}
int Member::getFlag(){
    return active;
}
