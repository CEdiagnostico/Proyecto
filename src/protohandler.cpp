#include"protohandler.h"


using namespace ce;
namespace proto {
    std::string createEvent(StructEvento &evento) {
        Evento protoEvent;
        protoEvent.set_type(evento.type);
        protoEvent.set_id(evento.id);
        protoEvent.set_x(evento.x);
        protoEvent.set_y(evento.y);
        return protoEvent.SerializeAsString();
    }

    StructEvento readEvent(std::string &input) {
        StructEvento result;
        Evento protoEvent;
        protoEvent.ParseFromString(input);
        result.type = protoEvent.type();
        if (protoEvent.has_id()) result.id = protoEvent.id();
        if (protoEvent.has_x()) result.x = protoEvent.x();
        if (protoEvent.has_y()) result.y = protoEvent.y();
        return result;
    }
}//namespace proto


