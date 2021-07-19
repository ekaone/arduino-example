#include <SoftwareSerial.h>
SoftwareSerial portOne(2, 3); // 2 = RX, 3 = TX

String dataString = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  portOne.begin(9600);
  
}

void loop() {
  portOne.listen();
  
  Serial.println("Data from port one:");
  while (portOne.available() > 0) {
    char inByte = portOne.read();
    //dataString += inByte;
    Serial.write(inByte);
  }

  Serial.println();
}
