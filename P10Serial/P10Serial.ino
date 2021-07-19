char serIn[40];

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  if(Serial.available()) {  
    int chars_in = 0;
    //keep reading and printing from serial untill there are bytes in the serial buffer
    while (Serial.available() > 0 && chars_in < 39){
        serIn[chars_in] = Serial.read();    //read Serial   
        Serial.write( byte(serIn[chars_in]));
        chars_in++;
    }
    //serIn[chars_in] = 0;
    //the serial buffer is over just go to the line (or pass your favorite stop char)               
    Serial.println();
  }
}



