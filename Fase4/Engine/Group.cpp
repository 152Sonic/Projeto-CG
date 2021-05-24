#include "Group.h"

Group::Group(string n, Transformation tf, vector<Group> g, vector<Ponto> p){
  this->nome = n;
  this->t = tf;
  this->filhos = g;
  this->pontos = p;
}

Group::Group(string nome, Transformation tf,string te, vector<Group> g, vector<Ponto> p, vector<Ponto> n, vector<Ponto> t){
  this->nome = nome;
  this->t = tf;
  this->textura = te;
  this->filhos = g;
  this->pontos = p;
  this->normais = n;
  this->textures = t;
}

void Group::setTextura(string t){
  this->textura = t;
}

string Group::getTextura(){
  return this->textura;
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

unsigned int Group:: getTexID(){
  return this->texID;
}

void Group::prep(){
  int tam = pontos.size();
  int n=0;
  int i;
  vector<float> v = vector<float>();
  vector<float> n5 = vector<float>();
  vector<float> t = vector<float>();

  for(i=0;i<tam;i++){
    v.push_back(pontos[i].getX());
    v.push_back(pontos[i].getY());
    v.push_back(pontos[i].getZ());
  }

  for(i=0;i<normais.size();i++){
    n5.push_back(normais[i].getX());
    n5.push_back(normais[i].getY());
    n5.push_back(normais[i].getZ());
  }cout << normais.size() << endl;

  for(i=0;i<textures.size();i++){
    t.push_back(textures[i].getX());
    t.push_back(textures[i].getY());
  }


  nvertices = v.size()/3;

  glGenBuffers(3,buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), v.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n5.size(), n5.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), t.data(), GL_STATIC_DRAW);

  criarTextura();

}

void Group::criarTextura(){
  unsigned char* data;
  string path = "../Engine/texturas/" + textura;
	ilGenImages(1, &ti);
	ilBindImage(ti);
	ilLoadImage((ILstring) path.c_str());
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	data = ilGetData();
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
  //glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Group::draw(){
  glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glNormalPointer(GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
	glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nvertices);
}
