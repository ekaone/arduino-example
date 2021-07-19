/*
 * MFRC522 - Library to use ARDUINO RFID MODULE KIT 13.56 MHZ WITH TAGS SPI W AND R BY COOQROBOT.
 * The library file MFRC522.h has a wealth of useful info. Please read it.
 * The functions are documented in MFRC522.cpp.
 *
 * Based on code Dr.Leong   ( WWW.B2CQSHOP.COM )
 * Created by Miguel Balboa (circuitito.com), Jan, 2012.
 * Rewritten by Søren Thing Andersen (access.thing.dk), fall of 2013 (Translation to English, refactored, comments, anti collision, cascade levels.)
 * Released into the public domain.
 *
 * Sample program showing how to read data from a PICC using a MFRC522 reader on the Arduino SPI interface.
 *----------------------------------------------------------------------------- empty_skull 
 * Aggiunti pin per arduino Mega
 * add pin configuration for arduino mega
 * http://mac86project.altervista.org/
 ----------------------------------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 *
 * The reader can be found on eBay for around 5 dollars. Search for "mf-rc522" on ebay.com. 
 */



#include <MFRC522.h>
#include <SPI.h>



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
    }
}
    
// menampilkan pembacaan RFID dalam bentuk dec
void printDec(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        //menampilkan data
     Serial.print(buffer[i] < 0x10 ? " 0" : " ");Serial.print(buffer[i], DEC);
    }
}
