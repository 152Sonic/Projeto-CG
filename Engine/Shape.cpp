#include "Shape.h"
#include <vector>

void Shape::inserePonto(Ponto p){
  this.Vertices.pushback(p);
}

int Shape::getSize(){
  return this.Vertices.size();
}

Ponto* Shape::getPonto(int i){
  return this.Vertices.at(i);
}
