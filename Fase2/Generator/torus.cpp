# include "torus.h"

void torus(double r1, double r2, double divb, string nome){
  double esp = r2 - r1;
  ofstream file(nome);

  double angle = (2 * M_PI) / divb;

  for(float i = 0; i < 2*M_PI; i+= angle){

    float x1 = r1 * sin(i);
    float y1 = 0;
    float z1 = r1 * cos(i);

    float x2 = r2 * sin(i);
    float y2 = 0;
    float z2 = r2 * cos(i);

    float x3 = r1 * sin(i + angle);
    float y3 = 0;
    float z3 = r1 * cos(i + angle);

    float x4 = r2 * sin(i + angle);
    float y4 = 0;
    float z4 = r2 * cos(i + angle);

    file << x1 << "," << y1 << "," << z1 << endl;
    file << x2 << "," << y2 << "," << z2 << endl;
    file << x3 << "," << y3 << "," << z3 << endl;

    file << x4 << "," << y4 << "," << z4 << endl;
    file << x3 << "," << y3 << "," << z3 << endl;
    file << x2 << "," << y2 << "," << z2 << endl;


  }
  file.close();
}
