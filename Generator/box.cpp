
#include "box.h"

void box(double comp, double alt, double larg, double div, string nome) {
    double x, y, z, xx, yy, zz;

    ofstream file(nome);
    double espcx = comp / div;
    double espcy = alt / div;
    double espcz = larg / div;

    // Frente e Tras

    z = larg / 2; zz = -z;
    y = -(alt / 2);
    for (int i = 0; i < div; i++) {
        x = -(comp / 2);
        xx = x + espcx;
        yy = y + espcy;
        for (int j = 0; j < div; j++) {

            file << x << "," << y << "," << z << endl;
            file << xx << "," << y << "," << z << endl;
            file << x << "," << yy << "," << z << endl;

            file << xx << "," << y << "," << z << endl;
            file << xx << "," << yy << "," << z << endl;
            file << x << "," << yy << "," << z << endl;

            file << x << "," << y << "," << zz << endl;
            file << x << "," << yy << "," << zz << endl;
            file << xx << "," << y << "," << zz << endl;

            file << xx << "," << y << "," << zz << endl;
            file << x << "," << yy << "," << zz << endl;
            file << xx << "," << yy << "," << zz << endl;

            x += espcx;
            xx += espcx;
        }

        y += espcy;
    }

    // Cima  e Baixo

    y = alt / 2; yy = -y;
    z = larg / 2;
    for (int i = 0; i < div; i++) {
        x = -(comp / 2);
        xx = x + espcx;
        zz = z - espcz;
        for (int j = 0; j < div; j++) {

            file << x << "," << y << "," << z << endl;
            file << xx << "," << y << "," << z << endl;
            file << x << "," << y << "," << zz << endl;

            file << xx << "," << y << "," << z << endl;
            file << xx << "," << y << "," << zz << endl;
            file << x << "," << y << "," << zz << endl;

            file << x << "," << yy << "," << z << endl;
            file << x << "," << yy << "," << zz << endl;
            file << xx << "," << yy << "," << z << endl;

            file << xx << "," << yy << "," << z << endl;
            file << x << "," << yy << "," << zz << endl;
            file << xx << "," << yy << "," << zz << endl;

            x += espcx;
            xx += espcx;
        }
        z -= espcz;
    }

    // Direita e Esquerda

    x = -(comp / 2); xx = -x;
    y = -(alt / 2);
    for (int i = 0; i < div; i++) {
        z = larg / 2;
        zz = z - espcz;
        yy = y + espcy;
        for (int j = 0; j < div; j++) {

            file << x << "," << y << "," << z << endl;
            file << x << "," << yy << "," << z << endl;
            file << x << "," << y << "," << zz << endl;

            file << x << "," << y << "," << zz << endl;
            file << x << "," << yy << "," << z << endl;
            file << x << "," << yy << "," << zz << endl;

            file << xx << "," << y << "," << z << endl;
            file << xx << "," << y << "," << zz << endl;
            file << xx << "," << yy << "," << z << endl;

            file << xx << "," << yy << "," << z << endl;
            file << xx << "," << y << "," << zz << endl;
            file << xx << "," << yy << "," << zz << endl;

            z -= espcz;
            zz -= espcz;
        }
        y += espcy;
    }
    file.close();
}
