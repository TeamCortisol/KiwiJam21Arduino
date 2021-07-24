#define RELAY 8


String sdata="";  // Initialised to nothing.


void setup() {
  Serial.begin(9600);

  pinMode(RELAY, OUTPUT);

  
  digitalWrite(RELAY, LOW);


  Serial.println("START");
 
}

void loop() {
  byte ch;
  
  if (Serial.available()) { //wait for command
    ch = Serial.read();
    sdata += (char)ch;
    if (ch=='\r') {  // command recieved
    sdata.trim();
    //Serial.println(sdata);
    
    //process command
    //Serial.println(sdata);

    if(sdata == "zap"){
      zap(100);
    }
    if(sdata == "zaap"){
      zap(500);
    }
    if(sdata == "zaaap"){
      zap(1000);
    }
    if(sdata == "pulse"){
      for(int i = 0; i < 3; i++){
        zap(100);
        delay(50);
      }
      
    }
    sdata = ""; // clr string
    }
  }
}

void zap(int timeToZap){ //time to zap in ms
  Serial.println("Zapping at " + String(timeToZap) + " ms");
  digitalWrite(RELAY, HIGH);
  delay(timeToZap);
  digitalWrite(RELAY, LOW);
}
