#ifndef Engine_Group_H
#define Engine_Group_H

#include <stdlib.h>
#include <vector>
#ifdef __APPLE__
#include <IL/il.h>
#include <GLUT/glut.h>
#else
#include <IL/il.h>
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Transformation.h"
#include "Ponto.h"

using  namespace std;

class Group{
        private:
        string nome;
        string textura;
        Transformation t;
        vector<Group> filhos =vector<Group>();
        vector<Ponto> pontos = vector<Ponto>();
        vector<Ponto> normais = vector<Ponto>();
        vector<Ponto> textures = vector<Ponto>();
        //VBO's
        GLuint buffer[3];
        GLsizei nvertices;
        //Texturas
        unsigned int ti, width, height;
	      ILuint texID;


        public:
        Group(string n, Transformation tf, vector<Group> g, vector<Ponto> p);
        Group(string nome, Transformation tf,string te, vector<Group> g, vector<Ponto> p,
	      vector<Ponto> n, vector<Ponto> t);
        void setTextura(string t);
        string getTextura();
        unsigned int getTexID();
        vector<Ponto> getPontos();
        vector<Group> getFilhos();
        Transformation getTrans();
        void imprime();
        void prep();
        void criarTextura();
        void draw();

};

#endif //Engine_Group_H
