// Code for controlling a 50 LED string of WS2811 lights for a Christmas tree.
// Originally written for the 2025 Infosec 716 pre-holiday party at the Bit Haven hackerspace

#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    50
#define BRIGHTNESS  128
#define FADEDELAY   75
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB

const int bottomButtonPin = 5;  // the number of the color change button pin
const int soundPin = 4; // the number of the sound sensor data pin
const int topButtonPin = 3;    // the number of the mode change button pin

int bottomButtonState = 0;
int topButtonState = 0;

CRGB leds[NUM_LEDS];
CRGB tempValue;

CRGB colorwheel[16];

int colorcounter = 1;
int colorstep = 0;

int modecounter = 0;

boolean soundVal = 0;

void setup() {

  // initialize the pushbutton pins as an input:
  pinMode(bottomButtonPin, INPUT);
  pinMode(soundPin, INPUT);
  pinMode(topButtonPin, INPUT);



    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(  BRIGHTNESS );   

    for (int i = 0; i < NUM_LEDS; i++){
      
      if (((i % 6) == 0) or ((i % 6) == 1))
        leds[i] = CRGB(0,255,0);
      else if (((i % 6) == 2) or ((i % 6) == 3))
        leds[i] = CRGB(255,0,0);
      else 
        leds[i] = CRGB(255,255,255);

    }

  FastLED.show();

  // Initialize the Serial Monitor

  Serial.begin(9600);

// colorwheel is an array containing the CRGB values of the classic IBM PC CGA palette

colorwheel[0] = CRGB(0x000000);
colorwheel[1] = CRGB(0x0000AA);
colorwheel[2] = CRGB(0x00AA00);
colorwheel[3] = CRGB(0x00AAAA);
colorwheel[4] = CRGB(0xAA0000);
colorwheel[5] = CRGB(0xAA00AA);
colorwheel[6] = CRGB(0xAA5500);
colorwheel[7] = CRGB(0xAAAAAA);
colorwheel[8] = CRGB(0x555555);
colorwheel[9] = CRGB(0x5555FF);
colorwheel[10] = CRGB(0x55FF55);
colorwheel[11] = CRGB(0x55FFFF);
colorwheel[12] = CRGB(0xFF5555);
colorwheel[13] = CRGB(0xFF55FF);
colorwheel[14] = CRGB(0xFFFF55);
colorwheel[15] = CRGB(0xFFFFFF);

}

void loop()
{

bottomButtonState = digitalRead(bottomButtonPin);
topButtonState = digitalRead(topButtonPin);
soundVal = digitalRead(soundPin);

if ( topButtonState == HIGH ) {

  modecounter++;
  Serial.println("MODE CHANGE!");
  Serial.println(modecounter);

  if ( ( modecounter % 6 ) == 0) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 1 ) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 2 ) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 3 ) {

    singleColor();
  }

  else if ( ( modecounter % 6 ) == 4 ) {

    singleColor();
  }

  else if ( ( modecounter % 6 ) == 5 ) {

    knightColors();
  }

}

if ( (bottomButtonState == HIGH) or (soundVal == LOW) ) {

  colorcounter++;
  Serial.println("COLOR CHANGE!");
  Serial.println(colorcounter);

  if ( ( modecounter % 6 ) == 0) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 1 ) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 2 ) {

    multipleColors();
  }

  else if ( ( modecounter % 6 ) == 3 ) {

    singleColor();
  }

  else if ( ( modecounter % 6 ) == 4 ) {

    singleColor();
  }

  else if ( ( modecounter % 6 ) == 5 ) {

    knightColors();
  }

}

if ( ( modecounter % 6 ) == 0) {

    for (int i=0; i<10; i++) {
      
      rotateForward();

    }
  }

  else if ( ( modecounter % 6 ) == 1 ) {

    for (int i=0; i<10; i++) {
      
      rotateBackward();

    }

  }

  else if ( ( modecounter % 6 ) == 2 ) {

         
      fadeOut();
      delay(50);
      rotateForward();
      fadeIn();
      delay(50);

    

  }

  else if ( ( modecounter % 6 ) == 3 ) {

    delay(2000);
  }

  else if ( ( modecounter % 6 ) == 4 ) {

        
      fadeOut();
      delay(50);
      fadeIn();
      delay(50);

    

  }

  else if ( ( modecounter % 6 ) == 5 ) {

    for (int i=0; i<47; i++) {
      
      rotateForward();

    }
    for (int i=0; i<47; i++) {
      
      rotateBackward();

    }

  }

delay(100);

}
  

void rotateForward()
{

  /* delay(3000); */

  tempValue = leds[NUM_LEDS - 1];

  for (int i = NUM_LEDS - 1; i > 0; i--) {

    leds[i] = leds[i - 1] ;
    delay(2);
     
  }

  FastLED.show();
  leds[0] = tempValue;

}

void rotateBackward()
{

  /* delay(3000); */

  tempValue = leds[0];

  for (int i = 0; i < NUM_LEDS - 1; i++) {

    leds[i] = leds[i + 1] ;
    delay(2);

  }

  FastLED.show(); 
  leds[NUM_LEDS - 1] = tempValue;

}

void singleColor() {

colorstep = (colorcounter % 16);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = colorwheel[ colorstep ];
  }

FastLED.show();

}

void multipleColors() {


colorstep = (colorcounter % 18);

    if ( (colorstep > 0) && (colorstep < 16) ) {
    
      for (int i = 0; i < NUM_LEDS; i++){
      
        if (((i % 4) == 0) or ((i % 4) == 1))
          leds[i] = CRGB(0xFFFFFF);
        else
          leds[i] = colorwheel[ colorstep ];

      }
    }

    else if (colorstep == 0) {

      for (int i = 0; i < NUM_LEDS; i++){
        leds[i] = colorwheel[ ( i % 16 ) ];
      }

    }

    else if (colorstep == 17) {

      for (int i = 0; i < NUM_LEDS; i++){
      
      if (((i % 6) == 0) or ((i % 6) == 1))
        leds[i] = CRGB(0,255,0);
      else if (((i % 6) == 2) or ((i % 6) == 3))
        leds[i] = CRGB(255,0,0);
      else 
        leds[i] = CRGB(255,255,255);

    }

    }

    else if (colorstep == 16) {

      for (int i = 0; i < NUM_LEDS; i++){
      
        if (((i % 6) == 0) or ((i % 6) == 1))
          leds[i] = CRGB(0xFFFFFF);
        else if (((i % 6) == 2) or ((i % 6) == 3))
          leds[i] = colorwheel[ 3 ];
        else
          leds[i] = colorwheel[ 5 ];

      }

    }


    

  FastLED.show();

}


void knightColors() {

colorstep = (colorcounter % 16);

  leds[0] = CRGB(255,255,255);
  leds[1] = colorwheel[ colorstep ];
  leds[2] = CRGB(255,255,255);

  for (int i = 3; i < NUM_LEDS; i++){
    leds[i] = CRGB(0,0,0);
  }

  FastLED.show();
}


void fadeOut() {

  for (int i = BRIGHTNESS; i >= 0 ; i=i-8){
    FastLED.setBrightness( i );
    FastLED.show();
    delay(FADEDELAY);
  }
 
FastLED.setBrightness(0);

delay(100);

}

void fadeIn() {

  
  for (int i = 0; i <= BRIGHTNESS; i=i+8){
    FastLED.setBrightness( i );
    FastLED.show();
    delay(FADEDELAY);
  }

delay(100);

}