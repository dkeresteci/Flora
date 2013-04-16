#include "Adafruit_FloraPixel.h"

/*****************************************************************************
 * Example sketch for driving Adafruit Flora pixels
 * Connect the pixel(s) to Digital 6 (low right hand)
 *****************************************************************************/

// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
#define BIT0 10
#define BIT1 9
#define BIT2 3 //SLC
#define BIT3 2 // SDA

#define waitms 150
Adafruit_FloraPixel strip = Adafruit_FloraPixel(8);



void setup() {
  
  pinMode(BIT0, INPUT);
  pinMode(BIT1, INPUT);
  pinMode(BIT2, INPUT);
  pinMode(BIT3, INPUT);
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
}


void loop() {
  // Some example procedures showing how to display to the pixels

  int setting = MUX_4x1(digitalRead(BIT0), digitalRead(BIT1), digitalRead(BIT2), digitalRead(BIT3)) ;
 // colorWipe(Color(0, 0, 0), 1);
  
  switch (setting) {
    
    //0
    case 0:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(255, 255 , 255), waitms );
    
      break;
     //1
    case 1:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(255, 0 , 0), waitms);
   
      break;
    //2
    case 2:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(0, 255 , 0), waitms );
     
      break;
    //3
    case 3:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(0, 0 , 255), waitms );
     
      break;       
    
    //4  
    case 4:
     rainbow(4); 
     
      break;
    //5
    case 5:
     rainbowCycle(4);
     
      break;
    //6
    case 6:
     rainbow(waitms/4);
     
      break;
    //7
    case 7:
    rainbowCycle(waitms/4);
     
      break;
    
    //8  
    case 8:
    rainbow(waitms);
    
      break;   
    //9
    case 9:
     rainbowCycle(waitms);
   
      break;
    //10
    case 10:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(0, 255 , 255), waitms);
     
      break;
    //11
    case 11:
    colorWipe(Color(0, 0, 0), 1);
    colorWipe(Color(255, 255 , 0), waitms);
     
      break;       
    
    //12  
    case 12:
    colorWipe(Color(0, 0, 0), 1);
     colorWipe(Color(255, 0 , 255), waitms);
   
      break;
    //13
    case 13:
     strip.setPixelColor(5, 255, 0, 0);
     
      break;
    //14
    case 14:
     strip.setPixelColor(6, 255, 0, 0);
     
      break;
    //15
    case 15:
     strip.setPixelColor(7, 255, 0, 0);
     
      break;
    default:
    rainbowCycle(16);  
     
     
  }
 strip.show();   // write all the pixels out
 //delay(1000);
 // if (digitalRead(BIT0) == HIGH) {
 // colorWipe(Color(255, 0, 0), 128);
 // colorWipe(Color(255, 255, 0), 128);
 // colorWipe(Color(0, 255, 0), 128);
 // colorWipe(Color(0, 255, 255), 128);
 // colorWipe(Color(0, 0, 255), 128);
  //colorWipe(Color(255, 0, 255), 128);
 // colorWipe(Color(255, 255, 255), 128);
 // delay(1000);

 //rainbowCycle(4);
 
}

void rainbow(uint8_t wait) {
  int i, j;

  for (j=0; j < 256; j++) {     // 3 cycles of all 256 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel( (i + j) % 255));
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// Slightly different, this one makes the rainbow wheel equally distributed 
// along the chain
void rainbowCycle(uint8_t wait) {
  int i, j;
  int repeat = 1; 

  for (j=0; j < 256 * repeat; j++) {     // 5 cycles of all 25 colors in the wheel
    for (i=0; i < strip.numPixels(); i++) {
      // tricky math! we use each pixel as a fraction of the full 96-color wheel
      // (thats the i / strip.numPixels() part)
      // Then add in j which makes the colors go around per pixel
      // the % 96 is to make the wheel cycle around
      strip.setPixelColor(i, Wheel( ((i * 256 / strip.numPixels()) + j) % 256) );
    }  
    strip.show();   // write all the pixels out
    delay(wait);
  }
}

// fill the dots one after the other with said color
// good for testing purposes
void colorWipe(RGBPixel c, uint8_t wait) {
  int i;

  for (i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

/* Helper functions */

// Create a 24 bit color value from R,G,B
RGBPixel Color(byte r, byte g, byte b)
{
  RGBPixel p;

  p.red = r;
  p.green = g;
  p.blue = b;

  return p;
}

//Input a value 0 to 255 to get a color value.
//The colours are a transition r - g -b - back to r
RGBPixel Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if (WheelPos < 170) {
    WheelPos -= 85;
    return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170; 
    return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

int MUX_4x1(int b0, int b1, int b2, int b3)
{
  int ans = 0;
 
   if (b0 == HIGH) {
      ans = ans + 1; 
     }
   if (b1 == HIGH) {
      ans = ans + 2; 
     }  
   if (b2 == HIGH) {
      ans = ans + 4; 
     }   
   if (b3 == HIGH) {
      ans = ans + 8; 
     }
   return ans;

}
