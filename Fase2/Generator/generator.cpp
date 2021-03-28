
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
#include "torus.h"


void help(){
    cout <<" -------------------------> MENU DE AJUDA <-------------------------"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|       * Plane lado plane.3d                                       |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|       * Box comp larg alt camadas box.3d                          |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|       * Cone raio altura camadasV camadasH cone.3d                |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|       * Sphere raio camadasV camadasH sphere.3d                   |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|-------------------------> Controlos 3D <--------------------------|"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<"|       * ROTAÇÃO DA CAMERA: w, a, s, d                             |"<< endl;
    cout <<"|                                                                   |"<< endl;
    cout <<" ----------------------------------><-------------------------------"<< endl;

}



int main (int argc, char** argv){
    if(argc == 2){
        if(strcmp(argv[1],"-h") == 0){
            help();
        }
    }
    else if(argc > 2){
        char path[1024];
        strcpy(path, "../3d/");

        if(strcmp(argv[1],"Plane") == 0){
            strcat(path, argv[3]);
            plano(atof(argv[2]), path);
        }
        else if(strcmp(argv[1],"Box") == 0){
            if(argc == 6){
                strcat(path, argv[5]);
                boxSDIV(atof(argv[2]), atof(argv[3]), atof(argv[4]),path);
            }
            else {
                strcat(path, argv[6]);
                box(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), path);
            }
        }
        else if(strcmp(argv[1],"Cone") == 0){
            strcat(path, argv[6]);
            cone(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]), path);
        }
        else if(strcmp(argv[1],"Torus") == 0){
            strcat(path, argv[5]);
            torus(atof(argv[2]), atof(argv[3]), atof(argv[4]), path);
        }
        else if(strcmp(argv[1],"Sphere") == 0){
            strcat(path, argv[5]);
            esfera(atof(argv[2]),atof(argv[3]),atof(argv[4]),path);
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
