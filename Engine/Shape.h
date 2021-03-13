#ifndef Engine_Shape_H
#define Engine_Shape_H

#include <vector>
#include "Ponto.h"

Class Shape{
private:
  std::vector<Ponto*> Vertices;

public:
  void inserePonto(Ponto* p);
  int getSize();
  Ponto* getPonto(int i);
}

#endif //Engine_Shape_H
