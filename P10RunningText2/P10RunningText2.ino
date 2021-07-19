#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_Black_16.h>

SoftDMD dmd(1,1);
// Jumlah panel p10 yang digunakan X, Y
DMD_TextBox box(dmd, 2, 1, 32, 16); 
// Set Box (dmd, x, y, Panjang, Lebar) 

void setup() {
  Serial.begin(9600);
  dmd.setBrightness(10); // Set kecerahan 0 - 255 
  dmd.selectFont(Arial_Black_16); // Font yang digunakan
  dmd.begin();     // memulai DMD 
}

void loop() {
  if (Serial.available() > 0) { //  tampilkan data ketika menerima data dari serial monitor:
    box.clear();
    box.print(Serial.readString()); // tampilkan data dari serial monitor
  }
}
