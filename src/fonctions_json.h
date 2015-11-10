#ifndef FONCTIONS_JSON_H
#define FONCTIONS_JSON_H

#include <iostream>

#include "json/json.h"

Json::Value saveAndLoad(Json::Value root, const char *file);
Json::Value loadJSONFile(const char *filePath);
void saveJSONFile(Json::Value root, const char* filePath);

#endif // FONCTIONS_JSON_H
