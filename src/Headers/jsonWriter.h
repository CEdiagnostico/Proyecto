//
// Created by roberto on 24/04/15.
//

#ifndef PROYECTO_JSONWRITER_H
#define PROYECTO_JSONWRITER_H

#include "List.h"
#include "../../libs/rapidjson/rapidjson.h"
#include "../../libs/rapidjson/document.h"
#include "../../libs/rapidjson/stringbuffer.h"
#include "../../libs/rapidjson/writer.h"
#include <cstdlib>
#include <string>

class jsonWriter {
public:
    void write(int,int,int,int,char[]);
    void writeP(int,int,int,int,int,char[]);
};


#endif //PROYECTO_JSONWRITER_H
