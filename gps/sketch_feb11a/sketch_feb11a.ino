
/*
### Get GPS data
1. This example is used to test SIM808 GPS/GPRS/GSM Shield's reading GPS data.
2. Open the SIM808_GetGPS example or copy these code to your project
3. Download and dial the function switch to Arduino
4. open mySerial helper
4. Place it outside, waiting for a few minutes and then it will send GPS data to mySerial

create on 2016/09/23, version: 1.0
by jason

*/
#include <DFRobot_sim808.h>
#include <SoftwareSerial.h>
#include <sim808.h>

#define PIN_TX    10
#define PIN_RX    11
SoftwareSerial mySerial(PIN_TX,PIN_RX);
DFRobot_SIM808 sim808(&mySerial);//Connect RX,TX,PWR,

//DFRobot_SIM808 sim808(&Serial);

void setup() {
  //Serial.begin(9600);
  mySerial.begin(9600);

  //******** Initialize sim808 module *************
  while(!sim808.init()) { 
      delay(1000);
      mySerial.print("Sim808 init error\r\n");
  }

  //************* Turn on the GPS power************
  if( sim808.attachGPS())
      mySerial.println("Open the GPS power success");
  else 
      mySerial.println("Open the GPS power failure");
  
}

void loop() {
   //************** Get GPS data *******************
   if (sim808.getGPS()) {
    mySerial.print(sim808.GPSdata.year);
    mySerial.print("/");
    mySerial.print(sim808.GPSdata.month);
    mySerial.print("/");
    mySerial.print(sim808.GPSdata.day);
    mySerial.print(" ");
    mySerial.print(sim808.GPSdata.hour);
    mySerial.print(":");
    mySerial.print(sim808.GPSdata.minute);
    mySerial.print(":");
    mySerial.print(sim808.GPSdata.second);
    mySerial.print(":");
    mySerial.println(sim808.GPSdata.centisecond);
    
    mySerial.print("latitude :");
    mySerial.println(sim808.GPSdata.lat,6);
    
    sim808.latitudeConverToDMS();
    mySerial.print("latitude :");
    mySerial.print(sim808.latDMS.degrees);
    mySerial.print("\^");
    mySerial.print(sim808.latDMS.minutes);
    mySerial.print("\'");
    mySerial.print(sim808.latDMS.seconeds,6);
    mySerial.println("\"");
    mySerial.print("longitude :");
    mySerial.println(sim808.GPSdata.lon,6);
    sim808.LongitudeConverToDMS();
    mySerial.print("longitude :");
    mySerial.print(sim808.longDMS.degrees);
    mySerial.print("\^");
    mySerial.print(sim808.longDMS.minutes);
    mySerial.print("\'");
    mySerial.print(sim808.longDMS.seconeds,6);
    mySerial.println("\"");
    
    mySerial.print("speed_kph :");
    mySerial.println(sim808.GPSdata.speed_kph);
    mySerial.print("heading :");
    mySerial.println(sim808.GPSdata.heading);

    //************* Turn off the GPS power ************
    sim808.detachGPS();
  }

}
