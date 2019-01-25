#include "ledlib.h"


int n;
int n_capas;
int n_ledcapa;
int n_anodos;

void voxelWrite(int x, int y, int z, bool estado,bool boolArray[]) {
  boolArray[x + y*n + z*n*n] = estado;
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
          voxelWrite(k, j,i, 1, boolArray);
      }
    }
  }
}
void perimetralCube( bool estado,bool boolArray[ ],int n_per,int base){
  // base:  Desplaza en la diagonal (0,0,0) a (8,8,8) el vertice donde se crean los perimetros
  // n_per: tamaño del perimetro 
  n_per=n_per-1;
  for (int i = 0; i<=n_per; i++ ) {
   //Bottom
    voxelWrite(i+base,0+base,0+base, estado,  boolArray);
    voxelWrite(0+base,i+base,0+base, estado,  boolArray);
    voxelWrite(i+base,n_per+base,0+base, estado,  boolArray);
    voxelWrite(n_per+base,i+base,0+base, estado,  boolArray);
    //Top
    voxelWrite(i+base,0+base,n_per+base, estado,  boolArray);
    voxelWrite(0+base,i+base,n_per+base, estado,  boolArray);
    voxelWrite(i+base,n_per+base,n_per+base, estado,  boolArray);
    voxelWrite(n_per+base,i+base,n_per+base, estado,  boolArray);    
    //Sides
    voxelWrite(0+base,0+base,i+base, estado,  boolArray);
    voxelWrite(n_per+base,0+base,i+base, estado,  boolArray);
    voxelWrite(0+base,n_per+base,i+base, estado,  boolArray);
    voxelWrite(n_per+base,n_per+base,i+base,estado,  boolArray);
  }
}
void perCuboPares(bool boolArray[ ]){
  //Perimetro de los cubos pares centrados  uno dentro de otro
  perimetralCube( true,boolArray,2,3);
  perimetralCube( true,boolArray,4,2);
  perimetralCube( true,boolArray,6,1);
  perimetralCube( true,boolArray,8,0);
}
void perCuboImpares(bool boolArray[ ],int vertex){
   //Perimetro de los cubos impares centrados  uno dentro de otro
  //Vertex (0,0,0)
  if(vertex == 0){
  perimetralCube( true,boolArray,1,3);
  perimetralCube( true,boolArray,3,2);
  perimetralCube( true,boolArray,5,1);
  perimetralCube( true,boolArray,7,0);
  }
  //Vertex (8,8,8)
  if(vertex == 1){
  perimetralCube( true,boolArray,1,4);
  perimetralCube( true,boolArray,3,3);
  perimetralCube( true,boolArray,5,2);
  perimetralCube( true,boolArray,7,1);
  }
}
