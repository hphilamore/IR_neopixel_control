// https://create.arduino.cc/projecthub/jimmyhuang92129/sharp-infrared-distance-sensor-11-30-15-ab22dc
#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define PIN 6           // LED strip pin  
#define sensorpin A0    // IR sensor pin 
#define COB_PIN A2      // COB LED strip pin
#define NUMPIXELS 200
#define NUM_EFFECTS 10
 

//byte selectedEffect=0;
int effect = EEPROM.read(0); 

const int sensor_max = 700;
const int sensor_min = 400;
float val = 0.0;
float old_val = 0.0;
int val_to_LED;
float weight = 0.4;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  effect++;
  if(effect >= NUM_EFFECTS){effect = 0;}
  EEPROM.write(0, effect);
}


void loop()
{
  //proximity_equaliser();

  //proximity_equaliser_reverse();

  //proximity_colour();

  //proximity_brightness();

  //pulse();

  //pulse2();

  //pulse_trigger();

  //heartThrob(30);

  //controlled_pulse();

  //controlled_pulse_reverse();

  //controlled_pulse_COB();
  
  Serial.println(effect);
  

  
  switch(effect) {
    
    case 0  : {
                while(1){
                  proximity_equaliser();
                }
              }

    case 1  : {
                while(1){
                  proximity_equaliser_reverse();
                }
              }

    case 2  : {
                while(1){
                  proximity_colour();
                }
              }

    case 3  : {
                while(1){
                  proximity_brightness();
                }

              }

    case 4  : {
                while(1){
                  pulse();
                }
              }

    case 5  : {
                while(1){
                  pulse2();
                }
              }

    case 6  : {
                while(1){
                  pulse_trigger();
                }
              }

    case 7  : {
                while(1){
                  heartThrob(30);
                }
              }

    case 8  : {
                while(1){
                  controlled_pulse();
                }
              }

   case 9  : {
                while(1){
                  controlled_pulse_reverse();
                }
              }
  }

}

//void changeEffect() {
//  Serial.println("change");
//  if (digitalRead (BUTTON) == HIGH) {
//    Serial.println("changing");
//    selectedEffect++;
//    EEPROM.put(0, selectedEffect);
//    asm volatile ("  jmp 0");
//  }
//}

void proximity_equaliser(){
  pixels.clear(); // Set all pixel colors to 'off'
  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  val_to_LED = map(val, sensor_min, sensor_max, 0, pixels.numPixels());
  val_to_LED = constrain(val_to_LED, 0, pixels.numPixels());
  //Serial.println(val);
  
  for(int i=0; i<val_to_LED; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(255, 48, 48)); 
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(100); 
}


void proximity_equaliser_reverse(){
  pixels.clear(); // Set all pixel colors to 'off'
  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  val_to_LED = map(val, sensor_min, sensor_max, 0, pixels.numPixels());
  val_to_LED = constrain(val_to_LED, 0, pixels.numPixels());
  val_to_LED = pixels.numPixels() - val_to_LED;
  //val_to_LED = pixels.numPixels() - map(val, sensor_min, sensor_max, 0, pixels.numPixels());
  //Serial.println(val);
  for(int i=0; i<val_to_LED; i++) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(255, 48, 48)); 
  }
  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(100); 
}



void proximity_colour(){
  weight = 0.15;
  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  int val_to_colour =  map(val, sensor_min, sensor_max, 0, 255);
  val_to_colour = constrain(val_to_colour,0,255);

//  Serial.print(val);
//  Serial.print('\t');
//  Serial.print(val_to_colour);
//  Serial.print('\t');
  int blue = 255-val_to_colour;
  //constrain(blue,0,255);
  int red = val_to_colour;
  //constrain(red,0,255);
//  Serial.print(blue);
//  Serial.print('\t');
//  Serial.print(red);
//  Serial.println();
  
  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel...
        pixels.setPixelColor(i, pixels.Color(red, 0, blue)); 
  }

  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(100); 
}


void proximity_brightness(){
  weight = 0.2;
  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  int val_to_colour =  map(val, sensor_min, sensor_max, 0, 255);
  val_to_colour = constrain(val_to_colour,0,255);
//  Serial.print(val);
//  Serial.print('\t');
//  Serial.println(val_to_colour);

  for(int i=0; i<pixels.numPixels(); i++) { // For each pixel...

    //pixels.setPixelColor(i, pixels.Color(val_to_colour, val_to_colour, val_to_colour)); 
    pixels.setPixelColor(i, pixels.Color(pixels.gamma8(val_to_colour), pixels.gamma8(val_to_colour), pixels.gamma8(val_to_colour))); 
    
  }

  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(100); 
}


void pulse(){
  for(int i=0; i<255; i++) { 
    for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
      pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));         //  Set pixel's color (in RAM)  
    }
    delay(5);
    pixels.show();
  }
  for(int i=255; i>0; i--) { 
    for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
      //pixels.setPixelColor(j, (i,i,i));         //  Set pixel's color (in RAM)  
      pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));  
    }
    delay(1);
    pixels.show();
  }
}


void pulse2(){
  for(int i=0; i<255; i++) { 
    for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
      pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));         //  Set pixel's color (in RAM)  
    }
//    val = weight * analogRead(sensorpin) + (1 - weight) * val;
//    int wait =  map(val, sensor_min, sensor_max, 5, 0);
    pixels.show();
  }
  for(int i=255; i>0; i--) { 
    for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip... 
      pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));  
    }
//    val = weight * analogRead(sensorpin) + (1 - weight) * val;
//    int wait =  map(val, sensor_min, sensor_max, 5, 0);
    pixels.show();
  }
}


void pulse_trigger(){

  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  
  if(val - old_val > 50){
    for(int i=0; i<255; i++) { 
      for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
        pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));         //  Set pixel's color (in RAM)  
      }
      delay(1);
      pixels.show();
    }
    for(int i=255; i>0; i--) { 
      for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
        //pixels.setPixelColor(j, (i,i,i));         //  Set pixel's color (in RAM)  
        pixels.setPixelColor(j, (pixels.gamma8(i), pixels.gamma8(i), pixels.gamma8(i)));  
      }
      delay(10);
      pixels.show();
    }
  }

  old_val = val; 
}

void heartThrob(uint8_t wait) {
  uint16_t i, j;
 
  //Adjust 60 and 90 to the starting and ending colors you want to fade between. 
  for(j=60; j<90; j++) {
    for(i=0; i<pixels.numPixels(); i++) {
      pixels.setPixelColor(i, Wheel((i+j) & 255));
    }
    pixels.show();
    delay(wait);
  }
}
 
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


//void controlled_pulse(){
// 
//      for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
//        pixels.setPixelColor(j, (0, 0, 255));         //  Set pixel's color (in RAM)  
//      }
//      delay(500);
//      pixels.show();
//
//      for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
//        //pixels.setPixelColor(j, (i,i,i));         //  Set pixel's color (in RAM)  
//        pixels.setPixelColor(j, (0, 0, 0));  
//      }
//      delay(500);
//      pixels.show();
//
//}



void controlled_pulse(){

      unsigned long previousMillis = 0;
      unsigned long interval = 1000;
      bool LED_state = true;
      int C;

      while(1){

        val = weight * analogRead(sensorpin) + (1 - weight) * val;
        //interval =  map(val, sensor_min, sensor_max, 0, 1000);
        interval = val; //constrain(interval, 0, 1000);
//        Serial.print(val);
//        Serial.print("\t");
//        Serial.println(interval);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval){

          if(LED_state){
            C = 255;
          }

          else{
            C = 0;
          }
                  
 
          for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
            pixels.setPixelColor(j, (C, C, C));         //  Set pixel's color (in RAM)  
          }
          
          pixels.show();

          LED_state = !LED_state;

          previousMillis = currentMillis;
        }
      }
}


void controlled_pulse_reverse(){

      unsigned long previousMillis = 0;
      unsigned long interval = 1000;
      bool LED_state = true;
      int C;

      while(1){

        val = weight * analogRead(sensorpin) + (1 - weight) * val;
        //interval =  map(val, sensor_min, sensor_max, 0, 1000);
        interval = 1000.0 - val; //constrain(interval, 0, 1000);
//        Serial.print(val);
//        Serial.print("\t");
//        Serial.println(interval);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval){

          if(LED_state){
            C = 255;
          }

          else{
            C = 0;
          }
                  
 
          for(int j=0; j<pixels.numPixels(); j++) { // For each pixel in strip...
            pixels.setPixelColor(j, (C, C, C));         //  Set pixel's color (in RAM)  
          }
          
          pixels.show();

          LED_state = !LED_state;

          previousMillis = currentMillis;
        }
      }
}

void controlled_pulse_COB(){

      unsigned long previousMillis = 0;
      unsigned long interval = 1000;
      bool LED_state = true;
      int C;

      while(1){

        val = weight * analogRead(sensorpin) + (1 - weight) * val;
        //interval =  map(val, sensor_min, sensor_max, 0, 1000);
        interval = val; //constrain(interval, 0, 1000);
        Serial.print(val);
        Serial.print("\t");
        Serial.println(interval);

        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval){

          if(LED_state){
            C = 255;
          }

          else{
            C = 0;
          }
                  
 
          digitalWrite(COB_PIN, LED_state);
          
          pixels.show();

          LED_state = !LED_state;

          previousMillis = currentMillis;
        }
      }
}


void proximity_brightness_COB(){
  weight = 0.2;
  val = weight * analogRead(sensorpin) + (1 - weight) * val;
  int val_to_colour =  map(val, sensor_min, sensor_max, 0, 255);
  val_to_colour = constrain(val_to_colour,0,255);
  Serial.print(val);
  Serial.print('\t');
  Serial.println(val_to_colour);

  analogWrite(COB_PIN, val_to_colour);

  pixels.show();   // Send the updated pixel colors to the hardware.
  delay(100); 
}
