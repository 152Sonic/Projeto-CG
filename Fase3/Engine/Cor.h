#ifndef Engine_Cor_H
#define Engine_Cor_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Cor{
        private:
        float r;
        float g;
        float b;

        public:
        Cor();
        Cor (float r, float g, float b);
        float getR();
        float getG();
        float getB();
        void setR(float a);
        void setG(float b);
        void setB(float c);
};

#endif //Engine_Cor_H
