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
  cout << this->nome << endl;
}
