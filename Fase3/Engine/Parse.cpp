#include "Parse.h"

vector<Group> groups = vector<Group>();
vector<Ponto> shape;

void parseTranslate(XMLElement* elemento, Translate *translate){
  if(elemento->Attribute("X"))
    translate->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    translate->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    translate->setZ(stof(elemento->Attribute("Z")));
}

void parseRotate(XMLElement* elemento, Rotate *rotate){
  if(elemento->Attribute("X"))
    rotate->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    rotate->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    rotate->setZ(stof(elemento->Attribute("Z")));
  if (elemento->Attribute("angle"))
    rotate->setAngle(stof(elemento->Attribute("angle")));
  else if (elemento->Attribute("time"))
    rotate->setTime(stof(elemento->Attribute("time")));
}

void parseScale(XMLElement* elemento, Scale *scale){
  if(elemento->Attribute("X"))
    scale->setX(stof(elemento->Attribute("X")));
  if (elemento->Attribute("Y"))
    scale->setY(stof(elemento->Attribute("Y")));
  if (elemento->Attribute("Z"))
    scale->setZ(stof(elemento->Attribute("Z")));
}

void parseCor(XMLElement* elemento, Cor *cor){
  if(elemento->Attribute("R"))
    cor->setR(stof(elemento->Attribute("R")));
  if (elemento->Attribute("G"))
    cor->setG(stof(elemento->Attribute("G")));
  if (elemento->Attribute("B"))
    cor->setB(stof(elemento->Attribute("B")));
}

void readFile(string fich) {
    ifstream file;
    file.open(fich.c_str());
    if (file.is_open()){
        string line;
        while (getline(file, line)) {
            Ponto p = Ponto(line);
            shape.push_back(p);
        }
        file.close();
    }
    else {
        printf("NAO ABRIU O FICHEIRO\n");
    }
}

void parseXML(XMLElement* group, vector<Group> *g){
  Rotate rotate = Rotate();
  Scale scale = Scale();
  Translate translate = Translate();
  Cor cor = Cor();

  for(XMLElement* elemento = group->FirstChildElement();(strcmp(elemento->Name(),"models")!=0); elemento = elemento -> NextSiblingElement()){
    if(strcmp(elemento->Name(),"translate")==0){
      if(elemento->Attribute("time")){
        translate.setTime(stof(elemento->Attribute("time")));
        for(XMLElement* elem = elemento->FirstChildElement();elem;elem = elem->NextSiblingElement()){
          if(strcmp(elem->Name(),"ponto")==0){
            Ponto p = Ponto(stof(elem->Attribute("X")),stof(elem->Attribute("Y")),stof(elem->Attribute("Z")));
            cout << p.getX() << endl;
            translate.addPonto(p);
          }
        }
        translate.desenhaCurvas();
      }
      else{
        parseTranslate(elemento, &translate);
      }
    }
      if(strcmp(elemento->Name(),"rotate")==0){
        parseRotate(elemento, &rotate);
      }
      if(strcmp(elemento->Name(),"scale")==0){
        parseScale(elemento, &scale);
      }
      if(strcmp(elemento->Name(),"cor")==0){
        parseCor(elemento, &cor);
      }
  }

  Transformation t = Transformation(rotate, scale, translate, cor);



  for(XMLElement* model = group->FirstChildElement("models")->FirstChildElement("model"); model; model= model->NextSiblingElement()){

    readFile(model->Attribute("file"));
    vector<Ponto> p1 = shape;
    shape.clear();
    vector<Group> filhos;
    if (group->FirstChildElement("group")) {
        XMLElement *f = group->FirstChildElement("group");
        for(;f;f = f->NextSiblingElement()){
            parseXML(f, &filhos);
      }
    }
    Group pai = Group(model->Attribute("file"), t, filhos,p1);
    pai.prep();
    pai.imprime();
    g->push_back(pai);
  }
}

  vector<Group> lerXML(string ficheiro) {
      XMLDocument docxml;

      if (!(docxml.LoadFile(ficheiro.c_str()))) {
          XMLElement* root = docxml.FirstChildElement();
          XMLElement* group = root -> FirstChildElement();
          //vector<Group> g = vector<Group>();
          if(group->FirstChildElement("group")){
            group = group->FirstChildElement("group");
          }
          for(group;group;group = group->NextSiblingElement()){
            parseXML(group, &groups);
          }
      }
      else {
          cout << "Ficheiro XML não foi encontrado" << endl;
      }
      return groups;
  }
