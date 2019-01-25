// LEDolas
//
#include <TimerOne.h>
#include "ledlib.h"
#define latchPin  10                          //Latch (Pin 12)
#define clockPin  11                          //Clock serie (Pin 11)
#define dataPin_anodo  8                      // DS (Pin 14) para anodos
#define INTERVALO 10                           //microsegundos entre interrupciones
#define INTERVALO2 100000
//Variables Interrupcion
//Variables Registros
byte byte_anodo;              // Almaceno los datos de los anodos
byte byte_catodo;             // Almaceno capa a encender
int nbytes;                   // Cuantos bytes se necesitan para enviar los anodos y los catodos
// Variables CUBO :
int capa = 0;
boolean cubo[512] ;           //Array que alamacena el valor de los anodos
byte *BytestoSend;            // Puntero
                              // Puntero Sinonima de la anterior --> byte BytetoSend[]; 


//Cabeceras de las funciones necesarias para el funcionamiento del cubo
int bytesNecesarios( ) ;
byte BooltoByte( boolean boolArray[ ], int celda);
void IntroducirCatodo(byte BytesArray[], int capa);
void MostrarByteArray(byte BytesArray[] );
void BuildByteArray(byte BytestoSend[], boolean boolArray[ ], int capa);
void mostrarCubo(boolean cubo[ ] );


void setup() {
  n = 8;                      //Tamaño del cubo
  n_capas = n;
  n_ledcapa = n * n;
  n_anodos = n * n * n;
  clearCube(cubo);            
  nbytes = bytesNecesarios( );    // Calculo cuantos bytes necesito segun el tamaño del cubo
  //Serial.begin(9600);
  //Serial.print("bytes necesarios: "); Serial.println(nbytes);
  BytestoSend = new byte[ nbytes];// Determino el tamaño que tiene el array despues de calcularlo
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin_anodo, OUTPUT);
  //Config Timer
  Timer1.initialize(INTERVALO);
  Timer1.attachInterrupt(Lanzacapas);  // attaches callback() as a timer overflow interrupt/ 
}
void loop() {
  
  //fullCube(cubo);
  //perCuboPares(cubo);
  //perCuboImpares(cubo,0);
  //perCuboImpares(cubo,1);

}


void Lanzacapas() {
  //Serial.print("Capa: "); Serial.println(capa);
  BuildByteArray(BytestoSend, cubo + capa * n_ledcapa, capa);
  IntroducirCatodo(BytestoSend, capa);
  MostrarByteArray(BytestoSend);
  capa++;
  if (capa == n) {
    capa = 0;
  }
}
void mostrarCubo(boolean cubo[ ] ) {
  for (int i = 0; i < n; i++) {
    Serial.println(" ");
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        Serial.print("  "); Serial.print(cubo[i + k * n + j * n * n]);
      }
    }
  }
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
  for (int i = 0; i <= nbytes - 1 ; i++) {
    shiftOut(dataPin_anodo, clockPin, LSBFIRST, BytesArray[i]);
    //Serial.print("Byte : "); Serial.println(BytesArray[i], BIN);
  }
  //HIGH  CUANDO PARO LA TRANSMISION

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
  //Serial.print("bytes necesarios: "); Serial.println(nbytes);
  return (bits / 8);
}
