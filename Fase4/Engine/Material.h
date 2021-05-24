#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Ponto.h"

using namespace std;

class Material{

    float diffuse[4];     // default: {0.8, 0.8, 0.8, 1};
    float ambient[4];     // default: {0.2, 0.2, 0.2, 1};
    float specular[4];     // default: {0, 0, 0, 1};
    float emission[4];     // default: {0, 0, 0, 1};

public:
    Material();
  //  Material(Ponto d, Ponto a, Ponto s, Ponto e);
    void draw();
    float* getDiffuse();
    float* getAmbient();
    float* getSpecular();
    float* getEmission();
    void setDiffuse(Ponto d);
    void setAmbient(Ponto d);
    void setSpecular(Ponto d);
    void setEmission(Ponto d);
};

#endif
