#include "Group.h"

Group::Group(string n, Transformation tf, vector<Group> g, vector<Ponto> p){
  this->nome = n;
  this->t = tf;
  this->filhos = g;
  this->pontos = p;
}

vector<Ponto> Group::getPontos(){
  return pontos;
}

vector<Group> Group::getFilhos(){
  return filhos;
}

Transformation Group::getTrans(){
  return this->t;
}

void Group::imprime(){
  cout << this->pontos[0].getY() << endl;
}

void Group::prep(){
  int tam = pontos.size();
  int n=0;
  int i = 0;
  vector<float> v = vector<float>();

  for(i;i<tam;i++){
    v.push_back(pontos[i].getX());
    v.push_back(pontos[i].getY());
    v.push_back(pontos[i].getZ());
  }

  nvertices = v.size()/3;

  glGenBuffers(1,buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), v.data(), GL_STATIC_DRAW);

}

void Group::draw(){
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3 , GL_FLOAT, 0 , 0);
	glDrawArrays(GL_TRIANGLES,0, nvertices);
}
