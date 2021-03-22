#include "Transformation.h"

Transformation::Transformation(){
  this->rt = Rotate::Rotate();
  this->sc = Scale::Scale();
  this->tr = Translate::Translate();
}

Transformation::Transformation(Rotate x, Scale y, Translate z){
  this->rt = x;
  this->sc = y;
  this->tr = z;
}
