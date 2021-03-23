#include "Transformation.h"
#include "Rotate.h"

Transformation::Transformation(){
  this->rt = Rotate();
  this->sc = Scale();
  this->tr = Translate();
}

Transformation::Transformation(Rotate x, Scale y, Translate z){
  this->rt = x;
  this->sc = y;
  this->tr = z;
}
  Rotate Transformation::getRotate(){
    return rt;
  }

  Scale Transformation::getScale(){
    return sc;
  }

  Translate Transformation::getTranslate(){
    return tr;
  }
