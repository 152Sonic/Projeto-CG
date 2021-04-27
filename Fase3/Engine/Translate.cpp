#include "Translate.h"

Translate::Translate(){
  this->time = 0;
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->pontos = {};
  this->curva = {};
}


Translate::Translate(float x, float y, float z){
  this->time = 0;
  this->x = x;
  this->y = y;
  this->z = z;
  this->pontos = {};
  this->curva = {};
}

Translate::Translate(float time, vector<Ponto> p){
  this->time = time;
  this->x = 0;
  this->y = 0;
  this->z = 0;
  this->pontos = p;
  this->curva = {};
}


float Translate::getX(){
  return this->x;
}

float Translate::getY(){
  return this->y;
}

float Translate::getZ(){
  return this->z;
}

float Translate::getTime(){
  return this->time;
}

vector<Ponto> Translate::getPontos(){
  return this->pontos;
}

vector<Ponto> Translate::getCurva(){
  return this->curva;
}

void Translate::setX(float x){
  this->x = x;
}

void Translate::setY(float y){
  this->y = y;
}

void Translate::setZ(float z){
  this->z = z;
}

void Translate::setTime(float time){
  this->time = time;
}

void Translate::addPonto(Ponto p){
  pontos.push_back(p);
}


void Translate::getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float *pos) {

  float ttt = pow(t,3);
  float tt = pow(t,2);
  float a[4];
  pos[0] = pos[1] = pos[2] = 0.0;
  // catmull-rom matrix
  float m[4][4] = {{-0.5f,  1.5f, -1.5f,  0.5f},
                   { 1.0f, -2.5f,  2.0f, -0.5f},
                   {-0.5f,  0.0f,  0.5f,  0.0f},
                   { 0.0f,  1.0f,  0.0f,  0.0f}};

  // Compute A = M * P

  a[0] = m[0][0]*ttt + m[1][0]*tt + m[2][0]*t + m[3][0];
  a[1] = m[0][1]*ttt + m[1][1]*tt + m[2][1]*t + m[3][1];
  a[2] = m[0][2]*ttt + m[1][2]*tt + m[2][2]*t + m[3][2];
  a[3] = m[0][3]*ttt + m[1][3]*tt + m[2][3]*t + m[3][3];

  pos[0] = a[0]*p0.getX() + a[1]*p1.getX() + a[2]*p2.getX() + a[3]*p3.getX();
  pos[1] = a[0]*p0.getY() + a[1]*p1.getY() + a[2]*p2.getY() + a[3]*p3.getY();
  pos[2] = a[0]*p0.getZ() + a[1]*p1.getZ() + a[2]*p2.getZ() + a[3]*p3.getZ();

  // Compute pos = T * A

  // compute deriv = T' * A

  // ...
}


// given  global t, returns the point in the curve
void Translate::getGlobalCatmullRomPoint(float gt, float *pos) {

  int tam = pontos.size();
  float t = gt * tam; // this is the real global t
  int index = floor(t);  // which segment
  t = t - index; // where within  the segment

  // indices store the points
  int indices[4];
  indices[0] = (index + tam-1)%tam;
  indices[1] = (indices[0]+1)%tam;
  indices[2] = (indices[1]+1)%tam;
  indices[3] = (indices[2]+1)%tam;

  getCatmullRomPoint(t, pontos[indices[0]], pontos[indices[1]], pontos[indices[2]], pontos[indices[3]], pos);
}

void Translate::desenhaCurvas(){
  float gt;
  float pos[3];

  for(gt=0;gt<1;gt+=0.01){
    getGlobalCatmullRomPoint(gt,pos);

    Ponto p = Ponto(pos[0],pos[1],pos[2]);
    //cout << pos[0] << "," << pos[1] << "," << pos[2] << endl;
    curva.push_back(p);
  }

}
