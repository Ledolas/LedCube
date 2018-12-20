// Rclock - ST-CP Pin 12
int latchPin = 10;
//Pin connected to SH_CP of 74HC595 Pin 11
int clockPin = 11;
////Pin connected to DS of 74HC595 Pin 14
int dataPinAnodo = 8;
int dataPinCatodo = 9;
//

//holders for infromation you're going to pass to shifting function
uint8_t dataAnodo = 0xFF;
uint8_t dataCatodo= 0xFF;


void setup() {
  // put your setup code here, to run once:
  pinMode(latchPin, OUTPUT); // Rclock - ST-CP Pin 12
  pinMode(clockPin, OUTPUT);
  pinMode(dataPinAnodo, OUTPUT);
  pinMode(dataPinCatodo, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(latchPin, 0);
  shiftOut(dataPinAnodo, clockPin, LSBFIRST, dataAnodo); 
  shiftOut(dataPinCatodo, clockPin, LSBFIRST, dataCatodo);
  digitalWrite(latchPin, 1);
  //delay(1);
  }
