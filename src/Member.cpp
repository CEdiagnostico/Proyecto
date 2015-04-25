//
// Created by roberto on 24/04/15.
//

#include "Member.h"

Member::Member(int paramFlag, int paramX, int paramY, int paramId, int paramType){
    active = static_cast<int*>(malloc(sizeof(int)));
    *active = paramFlag;
    x = static_cast<int*>(malloc(sizeof(int)));
    *x = paramX;
    y = static_cast<int*>(malloc(sizeof(int)));
    *y = paramY;
    id = static_cast<int*>(malloc(sizeof(int)));
    *id = paramId;
    type = static_cast<int*>(malloc(sizeof(int)));
    *type = paramType;
};
Member::~Member(){
    free(active);
    free(x);
    free(y);
    free(id);
};
void Member::setX(int newX){
    x=newX;
};
void Member::setY(int newY){
    y=newY;
};
void Member::changeFlag(){
    if(flag==0){
        flag=1;
    }else{
        flag=0;
    }
};
int Member::getX(){
    return *x;
};
int Member::getY(){
    return *y;
};
int Member::getId(){
    return *id;
};
int Member::getFlag(){
    return *active;
};