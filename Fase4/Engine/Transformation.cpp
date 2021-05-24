#include "Transformation.h"
#include "Rotate.h"

Transformation::Transformation(){
  this->rt = Rotate();
  this->sc = Scale();
  this->tr = Translate();
  this->cor = Cor();
}

Transformation::Transformation(Rotate x, Scale y, Translate z, Cor c){
  this->rt = x;
  this->sc = y;
  this->tr = z;
  this->cor = c;
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

  Cor Transformation::getCor(){
    return cor;
  }

  Material Transformation::getMaterial(){
    return m;
  }

  void Transformation::setMaterial(Material m){
    this->m = m;
  }
