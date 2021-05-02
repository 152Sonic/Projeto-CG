#ifndef Engine_Translate_H
#define Engine_Translate_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Ponto.h"
#include <math.h>

using  namespace std;

class Translate{
        private:
        float time;
        vector<Ponto> pontos;
        vector<Ponto> curva;
        float x;
        float y;
        float z;

        public:
        Translate();
        Translate (float x, float y, float z);
        Translate (float time, vector<Ponto> p);
        float getX();
        float getY();
        float getZ();
        float getTime();
        vector<Ponto> getPontos();
        vector<Ponto> getCurva();
        void setX(float a);
        void setY(float a);
        void setZ(float a);
        void setTime(float time);
        void addPonto(Ponto p);
        void getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float *pos,float* deriv);
        void getGlobalCatmullRomPoint(float gt, float *pos,float* deriv);
        void desenhaCurvas();
};

#endif //Engine_Translate_H
