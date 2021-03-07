
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "plano.h"
#include "box.h"
#include "cone.h"
#include "sphere.h"


int main (int argc, char** argv){
    if(argc > 1){
        if(strcmp(argv[1],"Plano") == 0){
            plano(atof(argv[2]), argv[3]);
        }
        else if(strcmp(argv[1],"Box") == 0){
            box(atof(argv[2]), atof(argv[3]), atof(argv[3]),atof(argv[4]),argv[5]);
        }
        else if(strcmp(argv[1],"Cone") == 0){
            cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
        }
        else if(strcmp(argv[1],"Esfera") == 0){
            esfera(atof(argv[2]),atof(argv[3]),atof(argv[4]),argv[5]);
        }
        else {
            printf("Figura impossivel\n");
        }
    }
    else {
        printf("Argumentos insuficientes\n");
    }
    return 0;
}


