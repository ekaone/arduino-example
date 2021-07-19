#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_Black_16.h>

SoftDMD dmd(1,1); // Jumlah panel p10 yang digunakan X, Y
DMD_TextBox box(dmd, 2, 1, 32, 16);  // Set Box (dmd, x, y, Panjang, Lebar) 

String stringSerial;
byte byteSerial;
char charSerial;
int intSerial;

void setup() {
  Serial.begin(9600);
  dmd.setBrightness(10); // Set kecerahan 0 - 255 
  dmd.selectFont(Arial_Black_16); // Font yang digunakan
  dmd.begin();     // start DMD 
}

void loop() {
  if (Serial.available() > 0) { //  tampilkan data ketika menerima data dari serial monitor:

    stringSerial = Serial.readString(); 
    byteSerial = Serial.read();
    charSerial = Serial.read();
    intSerial = Serial.read();
    
    box.clear();
    box.print(intSerial); // tampilkan data dari serial monitor
    Serial.println(intSerial, DEC);
    //Serial.println(charSerial);
  }
}
