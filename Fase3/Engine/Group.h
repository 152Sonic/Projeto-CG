#ifndef Engine_Group_H
#define Engine_Group_H

#include <stdlib.h>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Transformation.h"
#include "Ponto.h"

using  namespace std;

class Group{
        private:
        string nome;
        Transformation t;
        vector<Group> filhos =vector<Group>();
        vector<Ponto> pontos = vector<Ponto>();
        GLuint buffer[1];
        GLsizei nvertices;


        public:
        Group(string n, Transformation tf, vector<Group> g, vector<Ponto> p);
        vector<Ponto> getPontos();
        vector<Group> getFilhos();
        Transformation getTrans();
        void imprime();
        void prep();
        void draw();
};

#endif //Engine_Group_H
