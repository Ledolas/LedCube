extern int n; 
extern int n_capas;
extern int n_ledcapa; 
extern int n_anodos; 


void voxelWrite(int x, int y, int z, bool estado,bool boolArray[]);
void clearCube(bool boolArray[ ]);
void fullCube(bool boolArray[]);
void perimetralCube( bool estado,bool boolArray[ ],int n_per,int base);
void perCuboPares(bool boolArray[ ]);
void perCuboImpares(bool boolArray[ ],int vertex);
