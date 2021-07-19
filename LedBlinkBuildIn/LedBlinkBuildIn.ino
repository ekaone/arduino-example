void setup() {
  Serial.begin(9600);
  while(!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  if(Serial.available()) {
    int state = Serial.parseInt();
    
    if(state == 1) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Led ON");   
    } 

    if(state == 2) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Led OFF");    
    } 
  }
                        
}
