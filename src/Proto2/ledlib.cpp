#include "ledlib.h"


int n;
int n_capas;
int n_ledcapa;
int n_anodos;

void voxelWrite(int x, int y, int z, bool estado, bool boolArray[]) {
  boolArray[x + y * n + z * n * n] = estado;
}

void clearCube(bool boolArray[ ]) {
  for (int i = 0; i < n * n * n; i++) {
    boolArray[i] = 0 ;
  }
}
void fullCube(bool boolArray[]) {
  for (int i = 0; i < 8; i++ ) {
    for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 8; k++) {
        voxelWrite(k, j, i, 1, boolArray);
      }
    }
  }
}
void perimetralCube( bool estado, bool boolArray[ ], int n_per, int base) {
  // base:  Desplaza en la diagonal (0,0,0) a (8,8,8) el vertice donde se crean los perimetros
  // n_per: tamaño del perimetro
  n_per = n_per - 1;
  for (int i = 0; i <= n_per; i++ ) {
    //Bottom
    voxelWrite(i + base, 0 + base, 0 + base, estado,  boolArray);
    voxelWrite(0 + base, i + base, 0 + base, estado,  boolArray);
    voxelWrite(i + base, n_per + base, 0 + base, estado,  boolArray);
    voxelWrite(n_per + base, i + base, 0 + base, estado,  boolArray);
    //Top
    voxelWrite(i + base, 0 + base, n_per + base, estado,  boolArray);
    voxelWrite(0 + base, i + base, n_per + base, estado,  boolArray);
    voxelWrite(i + base, n_per + base, n_per + base, estado,  boolArray);
    voxelWrite(n_per + base, i + base, n_per + base, estado,  boolArray);
    //Sides
    voxelWrite(0 + base, 0 + base, i + base, estado,  boolArray);
    voxelWrite(n_per + base, 0 + base, i + base, estado,  boolArray);
    voxelWrite(0 + base, n_per + base, i + base, estado,  boolArray);
    voxelWrite(n_per + base, n_per + base, i + base, estado,  boolArray);
  }
}
void perCuboPares(bool boolArray[ ]) {
  //Perimetro de los cubos pares centrados  uno dentro de otro
  perimetralCube( true, boolArray, 2, 3);
  perimetralCube( true, boolArray, 4, 2);
  perimetralCube( true, boolArray, 6, 1);
  perimetralCube( true, boolArray, 8, 0);
}
void perCuboImpares(bool boolArray[ ], int vertex) {
  //Perimetro de los cubos impares centrados  uno dentro de otro
  //Vertex (0,0,0)
  if (vertex == 0) {
    perimetralCube( true, boolArray, 1, 3);
    perimetralCube( true, boolArray, 3, 2);
    perimetralCube( true, boolArray, 5, 1);
    perimetralCube( true, boolArray, 7, 0);
  }
  //Vertex (8,8,8)
  if (vertex == 1) {
    perimetralCube( true, boolArray, 1, 4);
    perimetralCube( true, boolArray, 3, 3);
    perimetralCube( true, boolArray, 5, 2);
    perimetralCube( true, boolArray, 7, 1);
  }
}
void planoX(int nplano, bool estado, bool boolArray[]) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++ ) {
      voxelWrite(nplano, i, j, estado, boolArray);
    }
  }
}
void planoY(int nplano, bool estado, bool boolArray[]) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++ ) {
      voxelWrite(i, nplano, j, estado, boolArray);
    }
  }
}
void planoZ(int nplano, bool estado, bool boolArray[]) {
  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++ ) {
      voxelWrite(j, i, nplano, estado, boolArray);
    }
  }
}
void caritacapa(int capa, bool boolArray[], int plano ) {
  //Plano = 1 --> X
  if (plano == 1) {
    lineWriteX(2, 0, 5, 0, capa, true, boolArray);
    lineWriteX(2, 7, 5, 7, capa, true, boolArray);
    lineWriteX(0, 2, 0, 5, capa, true, boolArray);
    lineWriteX(7, 2, 7, 5, capa, true, boolArray);
    voxelWrite(capa, 1, 1, true, boolArray);
    voxelWrite(capa, 6, 1, true, boolArray);
    voxelWrite(capa, 1, 6, true, boolArray);
    voxelWrite(capa, 6, 6, true, boolArray);
    //ojos
    voxelWrite(capa, 7 - 2, 7 - 2, true, boolArray);
    voxelWrite(capa, 7 - 5, 7 - 2, true, boolArray);
    //voxelWrite(capa, 7 - 4, 7 - 2, true, boolArray);
    //Sonrisa
    voxelWrite(capa, 7 - 1, 7 - 4, true, boolArray);
    voxelWrite(capa, 7 - 6, 7 - 4, true, boolArray);
    voxelWrite(capa, 7 - 2, 7 - 5, true, boolArray);
    voxelWrite(capa, 7 - 3, 7 - 5, true, boolArray);
    voxelWrite(capa, 7 - 4, 7 - 5, true, boolArray);
    voxelWrite(capa, 7 - 5, 7 - 5, true, boolArray);
  }
  //Plano = 2 --> Y
  if (plano == 2) {

    lineWriteY(2, 0, 5, 0, capa, true, boolArray);
    lineWriteY(2, 7, 5, 7, capa, true, boolArray);
    lineWriteY(0, 2, 0, 5, capa, true, boolArray);
    lineWriteY(7, 2, 7, 5, capa, true, boolArray);
    voxelWrite(1, capa, 1, true, boolArray);
    voxelWrite(6, capa, 1, true, boolArray);
    voxelWrite(1, capa, 6, true, boolArray);
    voxelWrite(6, capa, 6, true, boolArray);
    //ojos
    voxelWrite(7 - 2, capa, 7 - 2, true, boolArray);
    voxelWrite(7 - 5, capa, 7 - 2, true, boolArray);
    //Sonrisa
    voxelWrite(7 - 1, capa, 7 - 4, true, boolArray);
    voxelWrite(7 - 6, capa, 7 - 4, true, boolArray);
    voxelWrite(7 - 2, capa, 7 - 5, true, boolArray);
    voxelWrite(7 - 3, capa, 7 - 5, true, boolArray);
    voxelWrite(7 - 4, capa, 7 - 5, true, boolArray);
    voxelWrite(7 - 5, capa, 7 - 5, true, boolArray);

  }
  //Plano = 3 --> Z
  if (plano == 3) {
    //Circulo
    lineWriteZ(2, 0, 5, 0, capa, true, boolArray);
    lineWriteZ(2, 7, 5, 7, capa, true, boolArray);
    lineWriteZ(0, 2, 0, 5, capa, true, boolArray);
    lineWriteZ(7, 2, 7, 5, capa, true, boolArray);
    voxelWrite(1, 1, capa, true, boolArray);
    voxelWrite(1, 6, capa, true, boolArray);
    voxelWrite(6, 1, capa, true, boolArray);
    voxelWrite(6, 6, capa, true, boolArray);
    //ojos
    voxelWrite(2, 2, capa, true, boolArray);
    voxelWrite(2, 5, capa, true, boolArray);
    //Sonrisa
    voxelWrite(4, 1, capa, true, boolArray);
    voxelWrite(4, 6, capa, true, boolArray);
    voxelWrite(5, 2, capa, true, boolArray);
    voxelWrite(5, 3, capa, true, boolArray);
    voxelWrite(5, 4, capa, true, boolArray);
    voxelWrite(5, 5, capa, true, boolArray);
  }
}
void caritaCube(bool boolArray[]) {
  caritacapa(7, boolArray, 3);
  caritacapa(0, boolArray, 3);
  caritacapa(7, boolArray, 2);
  caritacapa(0, boolArray, 2);
  caritacapa(0, boolArray, 1);
  caritacapa(7, boolArray, 1);
}

void lineWriteZ(int x1, int y1 , int x2, int y2, int capa, bool estado, bool boolArray[]) {
  int x = x1 - x2;
  int y = y1 - y2;
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }

  if (x == 0) {
    //Vario y
    for (int i = 0; i < y + 1; i++) {
      voxelWrite(x1, y1 + i, capa, estado, boolArray);
    }
  }
  if (y == 0) {
    //Vario x
    for (int i = 0; i < x + 1; i++) {
      voxelWrite(x1 + i, y1, capa, estado, boolArray);
    }
  }
}
void lineWriteY(int x1, int y1 , int x2, int y2, int capa, bool estado, bool boolArray[]) {
  int x = x1 - x2;
  int y = y1 - y2;
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }

  if (x == 0) {
    //Vario y
    for (int i = 0; i < y + 1; i++) {
      voxelWrite(x1, capa, y1 + i, estado, boolArray);
    }
  }
  if (y == 0) {
    //Vario x
    for (int i = 0; i < x + 1; i++) {
      voxelWrite(x1 + i, capa, y1, estado, boolArray);
    }
  }
}
void lineWriteX(int x1, int y1 , int x2, int y2, int capa, bool estado, bool boolArray[]) {
  int x = x1 - x2;
  int y = y1 - y2;
  if (x < 0) {
    x = -x;
  }
  if (y < 0) {
    y = -y;
  }

  if (x == 0) {
    //Vario y
    for (int i = 0; i < y + 1; i++) {
      voxelWrite(capa, x1, y1 + i, estado, boolArray);
    }
  }
  if (y == 0) {
    //Vario x
    for (int i = 0; i < x + 1; i++) {
      voxelWrite(capa, x1 + i, y1, estado, boolArray);
    }
  }
}

void diagonalLine(bool boolArray[ ])
{
  for (int i = 0; i < n ; i++) {
    voxelWrite(i, i, i, true, boolArray);
    voxelWrite((n - 1) - i, i, i, true, boolArray);
    voxelWrite((n - 1) - i, (n - 1) - i, i, true, boolArray);
    voxelWrite((n - 1) - i, i, (n - 1) - i, true, boolArray);
  }
}

void moverPlanoZ(bool boolArray[ ])
{
  for (int i = 0 ; i < n * n * n ; i++) {
    if (i + n * n > (n * n * n - n * n)) {
      boolArray[i] = 0;
    } else {
      boolArray[i] = boolArray[i + n * n];
    }
  }
}
void moverPlanoX(bool boolArray[ ])
{
  for (int i = 0 ; i < n * n * n ; i++) {

    if (i + n  > n * n * n - n) {
      boolArray[(n * n * n - 1) - i] = boolArray[i];
    } else {
      boolArray[i] = boolArray[i + n ];
    }
  }
}

/*void voxelLluvia(bool boolArray[ ])
{
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
  voxelWrite(int(random(0, 8)), int(random(0, 8)), 6, true, cubo);
}*/
