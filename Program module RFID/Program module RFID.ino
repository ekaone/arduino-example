/* www.nyebarilmu.com */

#include <MFRC522.h> //meng-include-kan library RFID
#include <SPI.h> //serial Parallel Interface

//deklarasi penggunaan pin untuk RFID
#define SS 10
#define RST 9

byte nuidPICC[4];

MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key;

void setup() {
Serial.begin(9600); //Menggunakan 9600Bps untuk komunikasi serial monitor
SPI.begin(); //prosedur memulai SPI interface
rfid.PCD_Init(); //prosedur memulai pembacaan RFID

for (byte i = 0; i < 6; i++) {
key.keyByte[i] = 0xFF;
}

Serial.println(F("Kode NUID RFID")); //menuliskan pembacaan Kode NUID RFID di serial monitor
printHex(key.keyByte, MFRC522::MF_KEY_SIZE); //menampilkan data dalam bentuk heksa
}

void loop() {
if ( ! rfid.PICC_IsNewCardPresent()) // pengecekan adanya kartu RFID baru atau tidak
return;
// jika sudah pernah terbaca
if ( ! rfid.PICC_ReadCardSerial())
return;
  //prosedur menampilkan tipe data PICC
Serial.print(F("Tipe PICC : ")); ////menuliskan pembacaan Tipe PICC RFID di serial monitor
MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak); //command yang terdapat di library

Serial.println(rfid.PICC_GetTypeName(piccType));
if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI && piccType != MFRC522::PICC_TYPE_MIFARE_4K
 && piccType != MFRC522::PICC_TYPE_MIFARE_1K) 
{
 Serial.println(F("Kartu bukan tipe MIFARE Classic")); //menuliskan di serial monitor
 return;
 }

 if (rfid.uid.uidByte[3] != nuidPICC[3] || rfid.uid.uidByte[2] != nuidPICC[2] ||
 rfid.uid.uidByte[1] != nuidPICC[1] || rfid.uid.uidByte[0] != nuidPICC[0] )
{

 Serial.println(F("kartu RFID baru terdeteksi"));
 for (byte i = 0; i < 4; i++) { //perulangan sebanyak 4x penulisan data
 nuidPICC[i] = rfid.uid.uidByte[i];
 }

 Serial.println(F("The NUID tag is:"));
 Serial.print(F("Dalam bentuk hex: "));
 printHex(rfid.uid.uidByte, rfid.uid.size);
 Serial.println();
 //menuliskan dec
 Serial.print(F("Dalam bentuk dec: "));
 printDec(rfid.uid.uidByte, rfid.uid.size);Serial.println();
 }

else Serial.println(F("Kartu sudah dibawah sebelumnya"));
rfid.PICC_HaltA();rfid.PCD_StopCrypto1();
}

// memunculkan kode RFID dalam bentu heksa
void printHex(byte *buffer, byte bufferSize) {
for (byte i = 0; i < bufferSize; i++) {
    //menampilkan data
Serial.print(buffer[i] < 0x10 ? " 0" : " ");Serial.print(buffer[i], HEX);
}}

// menampilkan pembacaan RFID dalam bentuk dec
void printDec(byte *buffer, byte bufferSize) {
for (byte i = 0; i < bufferSize; i++) {
    //menampilkan data
 Serial.print(buffer[i] < 0x10 ? " 0" : " ");Serial.print(buffer[i], DEC);
}}