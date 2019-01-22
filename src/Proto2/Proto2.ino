//Este codigo lee un array bidimensional de tamaño [n][n*n]
//con la informacion de los anodos a encender en [n*n]
//y lo reparte en bytes para ir rellenando los registros asociados a los anodos.
//Los registros asociados a los catodos se rellenan segun la capa a encender del cubo,
//este valor lo determina [n]
// Asignacion de los Pines
#include <TimerOne.h>
#define latchPin  10        //Latch (Pin 12)
#define clockPin  11        //Clock serie (Pin 11)
#define dataPin_anodo  8      // DS (Pin 14) para anodos

//Variables Interrupcion
unsigned long previous_millis = 0;
unsigned long intervalo = 100; // intervalo en ms para la interrupcion
//Variables Registros
byte byte_anodo; // Almaceno los datos de los anodos
byte byte_catodo; // Almaceno capa a encender
int nbytes;// Cuantos bytes se necesitan para enviar los anodos
// Variables CUBO :
int n = 8; // cambiar dependiendo del Array a usar
int n_capas = n;
int n_ledcapa = n * n;
int n_anodos = n * n * n;
int capa = 0;
boolean primeraVez = true;
// Arrays --> Cambiar n dependiendo que array usemos
/*
  boolean cubo[2][4] = {
  {1, 0, 1, 0 } ,    //Capa 0
  {0, 1, 0, 1 }    //Capa 1
  };*/

/*
  boolean cubo[3][9] = {
  {1, 0, 1, 1, 0, 0, 0, 1, 1 },    //Capa 0
  {0, 0, 0, 1, 0, 0, 0, 1, 0 },    //Capa 1
  {0, 0, 0, 0, 0, 0, 0, 0, 1 }           //Capa 2
  };

  boolean cubo[4][16] = {
  // 0  1  2  3  4  5  6  7 |8  9 10 11 12 13 14 15|  Indices
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, //Capa 0
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, //Capa 1
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }, //Capa 2
  {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 }     //Capa 3
  };*/


boolean cubo[512] = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,// Capa 0
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 1
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 2
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 3
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 4
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 5
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,// Capa 6
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0  // Capa 7
  };

  /*
  boolean cubo[8][64] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 0
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 1
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 2
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 3
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 4
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 5
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },// Capa 6
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } // Capa 7
  };
*/

byte *BytestoSend; // Puntero
//byte BytetoSend[];// Puntero Sinonima de la anterior
//Cabeceras de las funciones
int bytesNecesarios( ) ;
byte BooltoByte( boolean boolArray[ ], int celda);
void IntroducirCatodo(byte BytesArray[], int capa);
void MostrarByteArray(byte BytesArray[] );
void BuildByteArray(byte BytestoSend[], boolean boolArray[ ], int capa);


void clearCubo(boolean boolArray[ ]) {
  for (int i = 0; i < n*n*n; i++) {
      boolArray[i] = 0 ;
     }
}
void voxelWrite(int x, int y, int z, bool estado,boolean boolArray[]) {
  boolArray[x + y*n + z*n*n] = 1;
  //Serial.print("* ******** ");Serial.println((int )boolArray); 
  //Serial.print("cubo[0][columna + fila * n] : ");Serial.println(cubo[0][columna + fila * n]);

}
void mostrarCubo(boolean cubo[ ] ){// no necesita el tamaño  // ---------------> PONER NLEDCAPA EN 
  for (int i = 0; i < n; i++) {
    Serial.println(" ");
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        Serial.print("  "); Serial.print(cubo[i + k*n + j * n*n]);
        
      }
    }
  }
}

void setup() {
  clearCubo(cubo);
  //voxelWrite(0, 0, 0, 1,  cubo);
  //voxelWrite(1, 0, 0, 1,  cubo);
  nbytes = bytesNecesarios( );// Calculo cuantos bytes necesito segun el cubo
  Serial.begin(9600);
  Serial.print("bytes necesarios: "); Serial.println(nbytes);
  BytestoSend = new byte[ nbytes];// Determino el tamaño que tiene el array despues de calcularlo
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin_anodo, OUTPUT);
  //Config Timer
  Timer1.initialize(10000000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(Lanzacapas);  // attaches callback() as a timer overflow interrupt/ PASA EL PUNTERO CUANDOD NO LLEVA ()

}

void loop() {
  // Animaciones
  //for (int i = 0; i < 8; i++ ) {
  if (primeraVez){
    voxelWrite(0, 0, 0, 1,  cubo);
    voxelWrite(1, 0, 0, 1,  cubo);
    //primeraVez=false;
  }
    //Serial.println((int )cubo);
  //}
  //;
  //Serial.println("soy ek lloopppp");
  //
}

void Lanzacapas() {
  //Serial.print("Capa: "); Serial.println(capa);
  BuildByteArray(BytestoSend, cubo+capa*n_ledcapa, capa);
  IntroducirCatodo(BytestoSend, capa);
  MostrarByteArray(BytestoSend);
  capa++;
  if (capa == n) {
    capa = 0;
  }
  mostrarCubo(cubo);
}
void BuildByteArray(byte BytestoSend[], boolean boolArray[ ], int capa) {

  for (int i = 0; i < nbytes; i++) {
    BytestoSend[i] = BooltoByte(boolArray, i * 8 );
  }
}

void MostrarByteArray(byte BytesArray[] ) {
  //Serial.print("nbytes : "); Serial.println(nbytes);
  //LOW  MIENTRAS TRANSMITO
  digitalWrite(latchPin, LOW);
  for (int i = nbytes - 1; i >= 0 ; i--) {
    shiftOut(dataPin_anodo, clockPin, LSBFIRST, BytesArray[i]);
    //Serial.print("Byte : "); Serial.println(BytesArray[i], BIN);
  }
  //HIGH  CUANDO PARO LA TRANSMISION

  //delay(5);
  digitalWrite(latchPin, HIGH);
}

void IntroducirCatodo(byte BytesArray[], int capa) {
  int numbyte = n_ledcapa / 8;
  int numbit = (n_ledcapa % 8) + capa;
  while (numbit >= 8) {
    numbyte++;
    numbit -= 8;
  }
  bitWrite(BytesArray[numbyte], 7 - numbit, 1);
}
byte BooltoByte( boolean boolArray[ ], int celda) {
  // Recibe u array booleano y un indice celda,
  // genera un byte con los 8 siguientes valores
  // Si no hay mas valores que introducir de la capa pone ceros.
  byte result = 0;
  for (int i = 0; i < 8; i++) {
    if (i < n_ledcapa  && ((i + celda ) <  n_ledcapa) ) {
      bitWrite(result, abs(i - 7)  , boolArray[i + celda ] );
    }
  }
  return  result;
}
int bytesNecesarios( ) {
  // Calcula cuantos bits tengo que generar para un cubo de tamaño n
  int bits = 0;
  if (n_ledcapa + n_capas  < 8) {
    bits = 8;
  } else {
    bits = 0;
    while (bits < n_ledcapa + n_capas) {
      //incremento cada 8 hasta que supere el valor necesario
      bits += 8;
    }
  }
  Serial.print("bytes necesarios: "); Serial.println(nbytes);
  return (bits / 8);
}
