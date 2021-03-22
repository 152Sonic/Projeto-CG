#ifndef Engine_Scale_H
#define Engine_Scale_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>

using  namespace std;

class Scale{
        private:
        float x;
        float y;
        float z;

        public:
        Scale();
        Scale (float x, float y, float z);
        float getX();
        float getY();
        float getZ();
        void setX(float a);
        void setY(float a);
        void setZ(float a);
};

#endif //Engine_Scale_H
