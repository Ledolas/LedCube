#include "ledlib.h"


int n; // cambiar dependiendo del Array a usar
int n_capas;
int n_ledcapa;
int n_anodos;

void voxelWrite(int x, int y, int z, bool estado,bool boolArray[]) {
  boolArray[x + y*n + z*n*n] = estado;
}
