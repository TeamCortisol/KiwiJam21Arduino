#include <FastLED.h>
#include <Servo.h>
#define NUM_LEDS 37 //24 in heart
#define DATA_PIN 6

#define SERVO 9

byte servoAngleInitial = 55; //55
byte servoAngleFinal = 85; //70

CRGB leds[NUM_LEDS];

Servo servo;

byte hue = 0;

String sdata="";  // Initialised to nothing.

int a = 0;
int beat[] = {479,476,478,478,475,481,490,487,483,488,490,492,487,488,492,499,501,503,496,498,507,516,516,508,496,486,494,495,497,501,503,513,549,628,725,794,717,545,383,297,271,281,295,310,354,427,
483,512,526,529,525,534,543,544,543,541,541,546,551,549,556,554,556,554,560,566,569,573,569,573,581,585,578,573,569,568,566,559,553,545,531,522,517,516,510,504,499,495,494,495,503,498,493,492,497,492,
490,488,496,500,497,495,492};
int size = sizeof(beat) / sizeof(int);

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  randomSeed(analogRead(1));
  Serial.println("START");

  
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

  for(int i = 0; i < 24; i++){
    leds[i] = CHSV(0,255,map(val,350,550,50,255));
    
  }
  FastLED.show();
  

  if (Serial.available()) { //wait for command
    byte ch = Serial.read();
    sdata += (char)ch;
    if (ch=='\r') {  // command recieved
    sdata.trim();

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
  Serial.println("ZAP");
  servo.attach(SERVO);
  servo.write(servoAngleFinal);
  
  for(int i = 0; i < 24; i++){
    leds[i] = CRGB(0,0,255);
  }
  for(int i = 25; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,255);
  }
  FastLED.show();
  delay(timeToZap);
  for(int i = 25; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
  servo.write(servoAngleInitial);
}
