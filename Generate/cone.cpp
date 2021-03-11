
#include "cone.h"

void cone(double raio, double h, double divb, double divh, string nome) {

    ofstream file(nome);
    double angle = (2 * M_PI) / divb;
    double espch = h / divh;
    double alt = -(h / 2);

    for (float i = 0; i < 2 * M_PI; i += angle) {

        float x1 = 0;
        float y1 = alt;
        float z1 = 0;

        float x2 = raio * sin(i + angle);
        float y2 = alt;
        float z2 = raio * cos(i + angle);

        float x3 = raio * sin(i);
        float y3 = alt;
        float z3 = raio * cos(i);

        file << x1 << "," << y1 << "," << z1 << endl;
        file << x2 << "," << y2 << "," << z2 << endl;
        file << x3 << "," << y3 << "," << z3 << endl;
    }

    for (int i = 0; i < divh; i++) {

        for (float j = 0; j < divb; j+= angle) {


            float x5 = (raio - (raio*i)/divh) * sin(j);
            float y5 = alt + i*espch;
            float z5 = (raio - (raio * i) / divh)* cos(j);

            float x4 = (raio - (raio * (i + 1)) / divh) * sin(j);
            float y4 = alt + (i + 1) * espch;
            float z4 = (raio - (raio * (i + 1)) / divh) * cos(j);

            float x6 = (raio - (raio * (i + 1)) / divh) * sin(j + angle);
            float y6 = alt + (i + 1) * espch;
            float z6 = (raio - (raio * (i + 1)) / divh) * cos(j + angle);

            float x7 = (raio - (raio * i) / divh) * sin(j + angle);
            float y7 = alt + i * espch;
            float z7 = (raio - (raio * i) / divh) * cos(j + angle);

            file << x5 << "," << y5 << "," << z5 << endl;
            file << x4 << "," << y4 << "," << z4 << endl;
            file << x6 << "," << y6 << "," << z6 << endl;

            file << x5 << "," << y5 << "," << z5 << endl;
            file << x7 << "," << y7 << "," << z7 << endl;
            file << x6 << "," << y6 << "," << z6 << endl;
        }

    }
    file.close();
}
