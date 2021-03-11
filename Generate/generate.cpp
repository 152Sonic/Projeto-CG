
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
        char path[1024];
        strcpy(path, "../3d/");
        
        if(strcmp(argv[1],"Plano") == 0){
            strcat(path, argv[3]);
            plano(atof(argv[2]), path);
        }
        else if(strcmp(argv[1],"Box") == 0){
            strcat(path, argv[5]);
            box(atof(argv[2]), atof(argv[3]), atof(argv[3]),atof(argv[4]),argv[5]);
        }
        else if(strcmp(argv[1],"Cone") == 0){
            strcat(path, argv[6]);
            cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), argv[6]);
        }
        else if(strcmp(argv[1],"Esfera") == 0){
            strcat(path, argv[5]);
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


