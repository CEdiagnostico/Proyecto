#ifndef PROTOHANDLER_H_INCLUDED
#define PROTOHANDLER_H_INCLUDED

#include"eventos.pb.h"



struct StructEvento
{
    std::string type;
    int id;
    std::string x;
    std::string y;
};
namespace proto {
    std::string createEvent(StructEvento &evento);

    StructEvento readEvent(std::string &input);
}





#endif // PROTOHANDLER_H_INCLUDED
