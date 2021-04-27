#ifndef Engine_Parse_H
#define Engine_Parse_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "tinyxml2.h"
#include "Group.h"

using namespace tinyxml2;
using  namespace std;

void parseXML(XMLElement* group, vector<Group> *g);
void parseScale(XMLElement* elemento, Scale *scale);
void parseRotate(XMLElement* elemento, Rotate *rotate);
void parseCor(XMLElement* elemento, Cor *cor);
void parseTranslate(XMLElement* elemento, Translate *translate);
void readFile(string fich);
vector<Group> lerXML(string ficheiro);

#endif //Engine_Parse_H
