//
// Created by roberto on 24/04/15.
//

#include "../Headers/jsonWriter.h"

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

void jsonWriter::writeP(int id, int flag, int x, int combustible, int vida, char json2[]){
    Document document;
    const char* json = "{\"Receptor\":\"0\", \"Flag\":\"0\", \"X\":\"0\", \"Combustible\":\"0\", \"Vida\":\"0\"}";
    document.Parse<0>(json);

    rapidjson::Value& a = document["Receptor"];
    a.SetInt(id);
    rapidjson::Value& b= document["Flag"];
    b.SetInt(flag);
    rapidjson::Value& c = document["X"];
    c.SetInt(x);
    rapidjson::Value& d = document["Combustible"];
    d.SetInt(combustible);
    rapidjson::Value& e = document["Vida"];
    d.SetInt(vida);

    rapidjson::StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    strcpy(json2, buffer.GetString());
};
