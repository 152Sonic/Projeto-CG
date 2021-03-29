//
// Created by Maria on 07/03/2021.
//

#include "sphere.h"

void esfera(double raio, double divb, double divh, string nome){

    ofstream file(nome);
    float espca = (2 * M_PI)/ divb;
    float espcb= M_PI / divh;
    float alpha,beta = M_PI/2;
    for(int i = 0; i < divh; i++){
        alpha = 0;
        for(int j = 0; j < divb; j++){

            float x1 = raio * sin(alpha) * cos(beta);
            float y1 = raio * sin(beta);
            float z1 = raio * cos(alpha) * cos(beta);

            float x2 = raio * sin(alpha + espca) * cos(beta - espcb);
            float y2 = raio * sin(beta - espcb);
            float z2 = raio * cos(alpha + espca) * cos(beta - espcb);

            float x3 = raio * sin(alpha) * cos(beta - espcb);
            float y3 = raio * sin(beta - espcb);
            float z3 = raio * cos(alpha) * cos(beta - espcb);

            float x4 = raio * sin(alpha + espca) * cos(beta);
            float y4 = raio * sin(beta);
            float z4 = raio * cos(alpha + espca) * cos(beta);

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;

            file << x1 << "," << y1 << "," << z1 << endl;
            file << x2 << "," << y2 << "," << z2 << endl;
            file << x3 << "," << y3 << "," << z3 << endl;

            alpha += espca;
        }
        beta -= espcb;
    }
}
