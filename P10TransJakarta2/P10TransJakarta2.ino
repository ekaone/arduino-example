
#include "SPI.h"        
#include "DMD.h"        
#include "TimerOne.h"
#include "Arial_black_16.h" 
/* you can remove the fonts if unused */
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1

DMD dmd( DISPLAYS_ACROSS , DISPLAYS_DOWN );

String inputString = "";         // a String to hold incoming data
String dataString = "";
bool stringComplete = false;  // whether the string is complete
//String textToScroll;

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

void setup()
{
   Serial.begin(9600);
   // reserve 200 bytes for the inputString:
   inputString.reserve(200);
   
   Timer1.initialize( 5000 );  
   Timer1.attachInterrupt( ScanDMD );
}

//String textToScroll="Hello, this will be displayed on the DMD";

void drawText( String dispString ) 
{
  dmd.clearScreen( true );
  dmd.selectFont( Arial_Black_16 );
  char newString[256];
  int sLength = dispString.length();
  dispString.toCharArray( newString, sLength+1 );
  dmd.drawMarquee( newString , sLength , ( 32*DISPLAYS_ACROSS )-1 ,0);
  long start=millis();
  long timer=start;
  long timer2=start;
  boolean ret=false;
  while( !ret ){
    // SET SPPED scroll here: 20ms more speedy
    if ( ( timer+70 ) < millis() ) {
      ret=dmd.stepMarquee( -1 , 0 );
      timer=millis();
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void loop()
{
  if (stringComplete) {
    Serial.println(inputString);
    // copy the string from serial to used on Led Panel
    dataString = inputString;
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  drawText(dataString);
}
