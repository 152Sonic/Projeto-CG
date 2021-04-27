#ifndef Engine_Transformation_H
#define Engine_Transformation_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <vector>
#include "Rotate.h"
#include "Scale.h"
#include "Translate.h"
#include "Cor.h"

using  namespace std;

class Transformation{
        private:
        Rotate rt;
        Scale sc;
        Translate tr;
        Cor cor;

        public:
        Transformation();
        Transformation (Rotate x, Scale y, Translate z, Cor c);
        Rotate getRotate();
        Scale getScale();
        Translate getTranslate();
        Cor getCor();
};

#endif //Engine_Transformation_H
