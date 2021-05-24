#ifndef Engine_Ponto_H
#define Engine_Ponto_H

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Ponto{
        private:
        float x;
        float y;
        float z;

        public:
        Ponto (float x, float y, float z);
        Ponto ();
        Ponto (string linha);
        float getX();
        float getY();
        float getZ();
        void setX(float x);
        void setY(float x);
        void setZ(float z);
};

#endif //Engine_Ponto_H
