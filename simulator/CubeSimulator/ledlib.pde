void init() {
  for (int x = 0; x<n; ++x) {
    for (int y = 0; y<n; ++y) {
      for (int z = 0; z<n; ++z) {
        cubo[x][z+y*n]=0;
      }
    }
  }
}

void setVoxel(int x, int y, int z ) {
  cubo[x][z+y*n]=1;
}
void clearVoxel(int x, int y, int z ) {
  cubo[x][z+y*n]=0;
}
void aniLectura() {
  for (int x = 0; x<n; ++x) {
    for (int y = 0; y<n; ++y) {
      for (int z = 0; z<n; ++z) {
        if (x==y && y==z) {
          cubo[x][z+y*n]=1;
        } else {
          cubo[x][z+y*n]=0;
        }
      }
    }
  }
}
void moverCapa() {

  for (int x = 0; x<n; ++x) {
    if (x==(n-1)) {
      cubo[0]=cubo[n-1];
    } else {
      cubo[x]=cubo[x+1];
    }
  }
}

void mostrararray(int a) {  
  for (int x = 0; x<n; ++x) {
    for (int y = 0; y<n; ++y) {
      for (int z = 0; z<n; ++z) {
        if (x==a*(y*z)*(y*z)/8) {
          cubo[x][z+y*n]=1;
        } else {
          cubo[x][z+y*n]=0;
        }
      }
    }
  }
}
void Plano(int nplano) {
  for (int y = 0; y<n; ++y) {
    for (int z = 0; z<n; ++z) {
      cubo[nplano][z+y*n]=1;
    }
  }
}