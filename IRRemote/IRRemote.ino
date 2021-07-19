
#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
const int yellowPin = 6;

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);

  pinMode(yellowPin, OUTPUT);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        
        switch(results.value){
          case 0xFF30CF: //Keypad button "1"
            digitalWrite(yellowPin, HIGH);
            delay(2000);
            digitalWrite(yellowPin, LOW);
        }
        irrecv.resume();
  }
}
