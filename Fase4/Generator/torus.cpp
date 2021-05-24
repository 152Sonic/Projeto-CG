# include "torus.h"

void torus(double r1, double r2, double divc, double divd, string nome){
  ofstream file(nome);

  double alpha = (2 * M_PI) / divc;
  double beta = (2 * M_PI) / divd;
  float c = 1/divc;
  float d = 1/divd;

  for(float i = 0; i <=(2*M_PI); i+= beta){

    for(float j = 0; j <= 2*M_PI; j+= alpha){

      float x1 = cos(j) * (cos(i) * r1 + r2);
      float y1 = sin(j) * (cos(i) * r1 + r2);
      float z1 = r1 * sin(i);

      float x2 = cos(j + beta) * (cos(i) * r1 + r2);
      float y2 = sin(j + beta) * (cos(i) * r1 + r2);
      float z2 = r1 * sin(i);

      float x3 = cos(j + beta) * (cos(i + alpha) * r1 + r2);
      float y3 = sin(j + beta) * (cos(i + alpha) * r1 + r2);
      float z3 = r1 * sin(i + alpha);

      float x4 = cos(j) * (cos(i + alpha) * r1 + r2);
      float y4 = sin(j) * (cos(i + alpha) * r1 + r2);
      float z4 = r1 * sin(i + alpha);

      file << x1 << "," << y1 << "," << z1 << endl;
      file << (x1-(cos(j)*r2))/r1 <<"," << -(y1-sin(j)*r2)/r1 << "," << -z1/r1 << endl;
      file << j*c << "," << i*d << "," << 0 << endl;
      file << x2 << "," << y2 << "," << z2 << endl;
      file << (x2-(cos(j+beta)*r2))/r1 <<"," << -(y2-sin(j+beta)*r2)/r1 << ","<<  -z2/r1 << endl;
      file << j*c << "," << i*d + d << "," << 0 << endl;
      file << x3 << "," << y3 << "," << z3 << endl;
      file << (x3-(cos(j+beta)*r2))/r1 <<"," << -(y3-sin(j+beta)*r2)/r1 << "," << -z3/r1 << endl;
      file << j*c+c << "," << i*d+d << "," << 0 << endl;

      file << x1 << "," << y1 << "," << z1 << endl;
      file << (x1-(cos(j)*r2))/r1 <<"," << -(y1-sin(j)*r2)/r1 << "," << -z1/r1 << endl;
      file << j*c << "," << i*d << "," << 0 << endl;
      file << x3 << "," << y3 << "," << z3 << endl;
      file << (x3-(cos(j+beta)*r2))/r1 <<"," << -(y3-sin(j+beta)*r2)/r1 << "," << -z3/r1 << endl;
      file << j*c+c << "," << i*d+d << "," << 0 << endl;
      file << x4 << "," << y4 << "," << z4 << endl;
      file << (x4-(cos(j)*r2))/r1 <<"," << -(y4-sin(j)*r2)/r1 << "," << -z4/r1 << endl;
      file << j*c+c << "," << i*d << "," << 0 << endl;


    }
  }

  file.close();
}
