#include "Ponto.h"


Ponto::Ponto(float x, float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
}

Ponto::Ponto(string line){
  /*vector<string> tokens;
  stringstream ss;
  string valor;
  while(getline(ss,valor,',')){
    tokens.push_back(valor);
  }*/
  char *linha,*token;

  linha = const_cast<char *>(line.c_str());
  token = strtok(linha, ",");
  this->x =atof(token);
  token = strtok(NULL, ",");
  this->y=atof(token);
  token = strtok(NULL, ",");
  this->z=atof(token);
}

float Ponto::getX(){
  return this->x;
}

float Ponto::getY(){
  return this->y;
}

float Ponto::getZ(){
  return this->z;
}
