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
void planoX(int nplano, bool estado, bool boolArray[]);
void planoY(int nplano, bool estado, bool boolArray[]);
void planoZ(int nplano, bool estado, bool boolArray[]);
void caritacapa(int capa,bool boolArray[],int plano );
void caritaCube(bool boolArray[]);
void lineWriteZ(int x1,int y1 ,int x2, int y2,int capa,bool estado,bool boolArray[]);
void lineWriteY(int x1,int y1 ,int x2, int y2,int capa,bool estado,bool boolArray[]);
void lineWriteX(int x1,int y1 ,int x2, int y2,int capa,bool estado,bool boolArray[]);
void diagonalLine(bool boolArray[ ]);
void moverPlanoZ(bool boolArray[ ]);
void moverPlanoX(bool boolArray[ ]);
void voxelLluvia(bool boolArray[ ]);
void seno(bool boolArray[ ]);
void numero(bool boolArray[ ]);
