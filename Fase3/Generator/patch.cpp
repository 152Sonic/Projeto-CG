#include "patch.h"
float* BezierCubica(float u, float* p0, float* p1, float* p2, float* p3){

  float t = 1.0 - u;
  float* ponto = new float[3];

  ponto[0] = pow(t,3) * p0[0] + 3 * u * pow(t,2) * p1[0] + 3 * pow(u,2) * t * p2[0] + pow(u,3) * p3[0];
  ponto[1] = pow(t,3) * p0[1] + 3 * u * pow(t,2) * p1[1] + 3 * pow(u,2) * t * p2[1] + pow(u,3) * p3[1];
  ponto[2] = pow(t,3) * p0[2] + 3 * u * pow(t,2) * p1[2] + 3 * pow(u,2) * t * p2[2] + pow(u,3) * p3[2];

  return ponto;
}

float* Bezier(float u, float v, int* patches, float** pontos){
  float calcv[4][3];
  float calcu[4][3];
  float* ponto = new float[3];
  float* res;
  int j = 0, r = 0;

  for(int i = 0; i < 16;i++){
    calcv[j][0] = pontos[patches[i]][0];
    calcv[j][1] = pontos[patches[i]][1];
    calcv[j][2] = pontos[patches[i]][2];

    j++;
    if((j % 4) == 0){
      ponto = BezierCubica(v,calcv[0],calcv[1], calcv[2], calcv[3]);
      calcu[r][0] = ponto[0];
      calcu[r][1] = ponto[1];
      calcu[r][2] = ponto[2];
      r++;
      j=0;
    }
  }

  res = BezierCubica(u,calcu[0], calcu[1], calcu[2], calcu[3]);

  return res;
}

void parse(string file, int tess, string nome){

  ofstream fileo(nome);
  ifstream filei(file);
  string line, aux;

  int i = 0;


  cout << "ola" << endl;

  if(filei.is_open()){
    getline(filei,line);
    int npatch = atoi(line.c_str());
    cout << npatch << endl;
    int** patches = new int*[npatch];

    cout << "ola" << endl;
    for(int r = 0; r<npatch; r++){
      getline(filei,line);
      patches[r] = new int[16];

      for(int j = 0; j<16; j++){
        i = line.find(",");
        aux = line.substr(0,i);
        patches[r][j] = atoi(aux.c_str());
        line.erase(0,i+1);
      }
    }

    getline(filei,line);
    int npontos = atoi(line.c_str());
    cout << npontos << endl;
    float** pontos = new float*[npontos];
    for(int r = 0; r<npontos; r++){
      getline(filei,line);
      pontos[r] = new float[3];
      for(int j = 0; j<3;j++){
        i = line.find(",");
        aux = line.substr(0,i);
        pontos[r][j] = atof(aux.c_str());
        line.erase(0,i+1);
      }
    }

    float t = 1.0/tess, u, v, u2, v2;
    float*** res = new float**[npatch];

      for(int r = 0; r<npatch; r++){
        res[r] = new float*[4];

        for(int nu = 0; nu < tess; nu++){

          for(int nv = 0; nv < tess; nv++){

            cout<< nv << endl;

            u = nu * t;
            v = nv * t;
            u2 = (nu + 1) * t;
            v2 = (nv + 1) * t;

            res[r][0] = Bezier(u,v, patches[r], pontos);
            res[r][1] = Bezier(u2,v, patches[r], pontos);
            res[r][2] = Bezier(u,v2, patches[r], pontos);
            res[r][3] = Bezier(u2,v2, patches[r], pontos);

            fileo << res[r][0][0] << "," << res[r][0][1] << "," << res[r][0][2] << endl;
            fileo << res[r][2][0] << "," << res[r][2][1] << "," << res[r][2][2] << endl;
            fileo << res[r][1][0] << "," << res[r][1][1] << "," << res[r][1][2] << endl;

            fileo << res[r][1][0] << "," << res[r][1][1] << "," << res[r][1][2] << endl;
            fileo << res[r][2][0] << "," << res[r][2][1] << "," << res[r][2][2] << endl;
            fileo << res[r][3][0] << "," << res[r][3][1] << "," << res[r][3][2] << endl;
        }
      }
    }
  }
  filei.close();
  fileo.close();
}
