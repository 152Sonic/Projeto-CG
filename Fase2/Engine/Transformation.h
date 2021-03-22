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

using  namespace std;

class Transformation{
        private:
        Rotate rt;
        Scale sc;
        Translate tr;

        public:
        Transformation();
        Transformation (Rotate x, Scale y, Translate z);
};

#endif //Engine_Transformation_H
