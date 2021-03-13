#include "Ponto.h"


Ponto::Ponto(float x, float y, float z){
  this.x = x;
  this.y = y;
  this.z = z;
}

Ponto::Ponto(string linha){
  vector<string> tokens;
  stringstream ss;
  string valor;
  while(getline(ss,valor,',')){
    tokens.pushback(valor);
  }
  this.x = atof(tokens[0].c_str());
  this.y = atof(tokens[1].c_str());
  this.y = atof(tokens[2].c_str());
}

float Ponto::getX(){
  return this.x;
}

float Ponto::getY(){
  return this.y;
}

float Ponto::getZ(){
  return this.z;
}
