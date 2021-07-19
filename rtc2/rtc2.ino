#include <DS3231.h>
 
DS3231  rtc(SDA, SCL); // inisialisasi penggunaan i2c
 
void setup()
{
  Serial.begin(115200); //set komunikasi baut serial monitor pada 115200
  rtc.begin();
  
  //setting pertama download program
  //rtc.setDate(16, 2, 2018);   //mensetting tanggal 25 mei 2017
  //rtc.setTime(00, 28, 00);     //menset jam 18:00:00
  //rtc.setDOW(FRIDAY);     //menset hari "Kamis"
 
//setelah didownload awal selesai, download kedua dengan memberi tanda komen "//"
}
 
void loop()
{
  Serial.print(rtc.getDOWStr()); //prosedur pembacaan hari
  Serial.print(" ");
  
  Serial.print(rtc.getDateStr()); //prosedur pembacaan tanggal
  Serial.print(" -- ");
 
  Serial.println(rtc.getTimeStr()); //prosedur pembacaan waktu
  
  delay (1000); //waktu tunda 1 detik per cycle
}
 
