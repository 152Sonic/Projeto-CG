#ifndef PROJETO_CG_PATCH_H
#define PROJETO_CG_PATCH_H

#define _USE_MATH_DEFINES

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

float* BezierCubica(float u, float* p0, float* p1, float* p2, float* p3);
float* Bezier(float u, float v, int* patches, float** pontos);
void parse(string file, int tess, string nome);
void vec(float *a, float *b, float *res);

#endif //PROJETO_CG_PATCH_H
