#include "Material.h"
#include <GL/glew.h>
#include <GL/glut.h>

Material::Material(){}
/*
Material::Material(Ponto d, Ponto a, Ponto s, Ponto e){
    diffuse[3] = -1;
    ambient[3] = -1;

    if(d != NULL) {
        diffuse[0] = d->getX();
        diffuse[1] = d->getY();
        diffuse[2] = d->getZ();
        diffuse[3] = 1;
    }

    if(a != NULL) {
        ambient[0] = a->getX();
        ambient[1] = a->getY();
        ambient[2] = a->getZ();
        ambient[3] = 1;
    }

    specular[0] = s->getX();
    specular[1] = s->getY();
    specular[2] = s->getZ();
    specular[3] = 1;

    emission[0] = e->getX();
    emission[1] = e->getY();
    emission[2] = e->getZ();
    emission[3] = 1;
}
*/
float* Material::getDiffuse(){
    return diffuse;
}

void Material::setDiffuse(Ponto p){
  diffuse[3] = -1;
  if(p.getX()!=-1) {
      diffuse[0] = p.getX();
      diffuse[1] = p.getY();
      diffuse[2] = p.getZ();
      diffuse[3] = 1;
  }
}

float* Material::getAmbient(){
    return ambient;
}

void Material::setAmbient(Ponto p){
  ambient[3] = -1;
  if(p.getX()!=-1) {
      ambient[0] = p.getX();
      ambient[1] = p.getY();
      ambient[2] = p.getZ();
      ambient[3] = 1;
  }
}

float* Material::getSpecular(){
    return specular;
}

void Material::setSpecular(Ponto p){
  specular[0] = p.getX();
  specular[1] = p.getY();
  specular[2] = p.getZ();
  specular[3] = 1;
}

float* Material::getEmission(){
    return emission;
}

void Material::setEmission(Ponto p){
  emission[0] = p.getX();
  emission[1] = p.getY();
  emission[2] = p.getZ();
  emission[3] = 1;
}

void Material::draw() {
    if(diffuse[3] != -1)
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    if(ambient[3] != -1)
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}
