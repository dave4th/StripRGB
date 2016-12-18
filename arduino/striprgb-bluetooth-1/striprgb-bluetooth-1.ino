#include <SoftwareSerial.h>
#include "VirtuinoBluetooth.h"                           // Include VirtuinoBluetooth library to your code


// Bluetooth HC-05
SoftwareSerial SerialBT(2, 3); // RX, TX
/*
 * Arduino - HC-05
 * 2 <- TX (3)
 * 3 -> RX (2)
 */

VirtuinoBluetooth virtuino(SerialBT,9600);       // Set SoftwareSerial baud rate.  -  Disable this line if you want to use hardware serial 

int greenLEDPin = 9;    // LED connected to digital pin 9
int redLEDPin = 10;     // LED connected to digital pin 10
int blueLEDPin = 6;    // LED connected to digital pin 6

// Valori di default/luminosita` all'accensione, giusto per vedere che e` acceso ;)
int GreenMemo = 100;
int RedMemo = 100;
int BlueMemo = 100;

/*
 * Sembra che con "Virtuino", non si  possibibile utilizzare
 * i 'delay', quindi utilizzo l'escamotage del programma
 * preso dalla demo: BlinkWithoutDelay
 */
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 3000;           // interval at which to blink (milliseconds)



void setup() {

  Serial.begin(9600);  // Inizializzo la porta seriale
  //SerialBT.begin(9600);

  //virtuino.DEBUG=true;               // set this value TRUE to enable the serial monitor status

  // set the digital pins as outputs
  pinMode(greenLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
}

void loop() {

  virtuino.run();           //  neccesary command to communicate with Virtuino android app

  /*
   * Credo di dover appoggiare a variabile tutti i valori 
   * da/per virtuino.
   */
  int Enable=virtuino.vDigitalMemoryRead(0);    // DV0
  int RED=virtuino.vMemoryRead(0);       // read analog virtual memory
  int GREEN=virtuino.vMemoryRead(1);       // read analog virtual memory
  int BLUE=virtuino.vMemoryRead(2);       // read analog virtual memory

    // Se e Ogni volta che premo il tasto II Pause Red, uso un valore random
    if ( Enable == HIGH ) {
      virtuino.vDigitalMemoryWrite(1,HIGH);    // DV1
      // check to see if it's time to blink the LED; that is, if the
      // difference between the current time and last time you blinked
      // the LED is bigger than the interval at which you want to
      // blink the LED.
      unsigned long currentMillis = millis();

      if (currentMillis - previousMillis >= interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        // Perche` utilizzando range di 5, 255/5=51
        RedMemo = random(52)*5;
        GreenMemo = random(52)*5;
        BlueMemo = random(52)*5;
      }
    }
    else {
      virtuino.vDigitalMemoryWrite(1,LOW);    // DV1
      RedMemo = RED;
      GreenMemo = GREEN;
      BlueMemo = BLUE;
    }

  analogWrite(redLEDPin, RedMemo);
  analogWrite(greenLEDPin, GreenMemo);
  analogWrite(blueLEDPin, BlueMemo);

/* DEBUG
Serial.println("RED: "+String(RED));
Serial.println("GREEN: "+String(GREEN));
Serial.println("BLUE: "+String(BLUE));
//Serial.println(redLEDPin);
//Serial.println(greenLEDPin);
//Serial.println(blueLEDPin);
Serial.println(RedMemo);
Serial.println(GreenMemo);
Serial.println(BlueMemo);

Serial.print("Enable: ");
Serial.println(Enable);
Serial.println(Disable);
Serial.println(virtuino.vDigitalMemoryRead(2));
Serial.println(RED);
Serial.println(GREEN);
Serial.println(BLUE);
*/

//delay(3000); // Virtuino s'incavola !
}
