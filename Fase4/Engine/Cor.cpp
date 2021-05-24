#include "Cor.h"


Cor::Cor(){
  this->r = 1;
  this->g = 1;
  this->b = 1;
}

Cor::Cor(float x, float y, float z){
  this->r = x;
  this->g = y;
  this->b = z;
}


float Cor::getR(){
  return this->r;
}

float Cor::getG(){
  return this->g;
}

float Cor::getB(){
  return this->b;
}

void Cor::setR(float x){
  this->r = x;
}

void Cor::setG(float y){
  this->g = y;
}

void Cor::setB(float z){
  this->b = z;
}
