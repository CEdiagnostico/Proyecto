//
// Created by roberto on 24/04/15.
//

#include "jsonWriter.h"
#include "../libs/rapidjson/rapidjson.h"
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"
#include <cstdlib>
#include <string>

using namespace rapidjson;

void jsonWriter::write(int id, int flag, int x, int y, char json2[]){
    Document document;
    const char* json = "{\"Receptor\":\"0\", \"Flag\":\"0\", \"X\":\"0\", \"Y\":\"0\"}";
    document.Parse<0>(json);

    rapidjson::Value& a = document["Receptor"];
    a.SetInt(id);
    rapidjson::Value& b= document["Flag"];
    b.SetInt(flag);
    rapidjson::Value& c = document["X"];
    c.SetInt(x);
    rapidjson::Value& d = document["Y"];
    d.SetInt(y);

    rapidjson::StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    strcpy(json2, buffer.GetString());
};
