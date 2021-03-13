
#include "plano.h"

void plano(float side, string nome) {
    ofstream file(nome);

    float x, y, z;

    x = side / 2;
    z = side / 2;
    y = 0;

//Triangulo 1
    file << x << "," << y << "," << z << endl;
    file << x << "," << y << "," << -z << endl;
    file << -x << "," << y << "," << z << endl;

//Triangulo 2
    file << -x << "," << y << "," << -z << endl;
    file << -x << "," << y << "," << z << endl;
    file << x << "," << y << "," << -z << endl;

    file.close();
}
