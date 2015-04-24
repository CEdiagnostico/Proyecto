//
// Created by roberto on 24/04/15.
//

#include "jsonWriter.h"

char* jsonWriter::write(int id, int type, int x, int y){
    char *message = static_cast<char*>(malloc(sizeof(char)*1000));
    Document document;
    const char* json = "{\"Receptor\":\"0\", \"Tipo\":\"0\", \"X\":\"0\", \"Y\":0}";
    document.Parse<0>(json);

    rapidjson::Value& s = document["Receptor"];
    s.SetInt(id);
    s = document["Tipo"];
    s.SetInt(type);
    s = document["X"];
    s.SetInt(x);
    s = document["Y"];
    s.SetInt(y);

    rapidjson::StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    char* json2 = static_cast<char*>(malloc(sizeof(char)*1024));
    strcpy(*json2, buffer.GetString());
    return json;
};
