#define RELAY 8


String sdata="";  // Initialised to nothing.

int a = 0;
int beat[] = {479,476,478,478,475,481,490,487,483,488,490,492,487,488,492,499,501,503,496,498,507,516,516,508,496,486,494,495,497,501,503,513,549,628,725,794,717,545,383,297,271,281,295,310,354,427,
483,512,526,529,525,534,543,544,543,541,541,546,551,549,556,554,556,554,560,566,569,573,569,573,581,585,578,573,569,568,566,559,553,545,531,522,517,516,510,504,499,495,494,495,503,498,493,492,497,492,
490,488,496,500,497,495,492};
int size = sizeof(beat) / sizeof(int);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  // Serial.println("START");
  randomSeed(analogRead(1));
}


void loop() {

  int randNumber = random(-10, 10);
  int val = beat[a] + randNumber;
  a++;
  if (a >= size) {
    a = 0;
  }
  char str[40];
  sprintf(str, "%d", val);
  Serial.println(str);

  
  if (Serial.available()) { //wait for command
    byte ch = Serial.read();
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
  
  delay(1);
}

void zap(int timeToZap){ //time to zap in ms
//  Serial.println("Zapping at " + String(timeToZap) + " ms");
  digitalWrite(RELAY, HIGH);
  delay(timeToZap);
  digitalWrite(RELAY, LOW);
}
