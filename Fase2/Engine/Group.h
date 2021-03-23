#ifndef Engine_Group_H
#define Engine_Group_H

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

        public:
        Group(string n, Transformation tf, vector<Group> g, vector<Ponto> p);
        vector<Ponto> getPontos();
        vector<Group> getFilhos();
        Transformation getTrans();
        void imprime();
};

#endif //Engine_Group_H
