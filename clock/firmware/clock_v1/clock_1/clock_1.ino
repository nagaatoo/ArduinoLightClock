#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <RTClib.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      252


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
RTC_DS1307 RTC;
DateTime now = RTC.now();
uint16_t  j, k, min_old_1=0, min_old_2=0, hour_old_1=0, hour_old_2=0;

byte digits[10][7] = {{0,1,1,1,1,1,1},  // Digit 0
                     {0,1,0,0,0,0,1},   // Digit 1
                     {1,1,1,0,1,1,0},   // Digit 2
                     {1,1,1,0,0,1,1},   // Digit 3
                     {1,1,0,1,0,0,1},   // Digit 4
                     {1,0,1,1,0,1,1},   // Digit 5
                     {1,0,1,1,1,1,1},   // Digit 6
                     {0,1,1,0,0,0,1},   // Digit 7
                     {1,1,1,1,1,1,1},   // Digit 8
                     {1,1,1,1,0,1,1}};  // Digit 9 | 2D Array for numbers on 7 segment

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
    RTC.begin();
  pixels.begin(); // This initializes the NeoPixel library.
}
byte sim = 0;


void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

//  for(int i=0;i<NUMPIXELS;i++){
//
//    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
//    pixels.setPixelColor(i, pixels.Color(0,150,0)); // Moderately bright green color.
//
//    pixels.show(); // This sends the updated pixel color to the hardware.
//
//    delay(delayval); // Delay for a period of time (in milliseconds).
// 
//
//   Start numbers: 1-st is 0 
//                  2-d is 63
//                  3-d is 126
//                  4-th is 189
//
 
  clockNow();
}


void clockNow()
{
   
   uint16_t mins_1=now.minute()/10, mins_2=now.minute()%10, hour_1=now.hour()/10, hour_2=now.hour()%10;
   

   if(mins_1!=min_old_1)
   {
        numberPix(mins_1,2);
        min_old_1=mins_1;
   }
   else if(mins_2!=min_old_2)
   {
        numberPix(mins_2,3);
        min_old_2=mins_2;
   }
   else if(hour_1!=hour_old_1)
   {
        numberPix(hour_1,0);
        hour_old_1=hour_1;         
   }
   else if(hour_2!=hour_old_2)
   {
        numberPix(hour_2,1);
        hour_old_2=hour_2;         
   }
   
}


////////////////////////////////////////////////////////////////////////////////////
//num - цифра; ind1 - номер табло; 
void numberPix(uint16_t num ,uint16_t ind1)
{ uint16_t ind;
  
   
  switch(ind1)
  {
    case 0: ind=0;break;
    case 1: ind=63;break;
    case 2: ind=126;break;
    case 3: ind=189;break;
    default: return;
  }
   delay(500);
   rainbowPix(ind);
    for (uint16_t i=0; i<7; i++) {
      if (digits[num][i]) {
      
          for (k=ind; k<ind+9; k++)
          {
            pixels.setPixelColor(((i*9)+k), pixels.Color(0,0,255));
             pixels.show();
            }         
      }
      else
        {
          for (k=ind; k<ind+9; k++)
          {
            pixels.setPixelColor(((i*9)+k), pixels.Color(0,0,0));
             pixels.show();
          }     
    }
        
}
 
  
}


//explosion rainbow trigger
void rainbowPix(uint16_t ind)
{
  uint16_t color1;
  uint16_t color2;
  uint16_t count=0;
  uint16_t i_quaet=0;
 
      for (uint16_t k_quaet=ind;k_quaet<ind+9;k_quaet++)
      {
        if (count%2==0)
        {
          color1=255;
          color2=0; 
        }
        else
        {
          color1=0;
          color2=255;
        }
        pixels.setPixelColor((i_quaet*9)+k_quaet, pixels.Color(color1,color2,0));
        pixels.setPixelColor((i_quaet+3*9)+ind+8-count, pixels.Color(color1,color2,0));
        pixels.setPixelColor((i_quaet+4*9)+k_quaet, pixels.Color(color1,color2,0));
        pixels.show();
        delay(50);
        count++;
      }
  
    count =0;
    i_quaet=0;
      for (uint16_t k_quaet=ind;k_quaet<ind+9;k_quaet++)
      {
        if (count%2==0)
        {
          color1=255;
          color2=0; 
        }
        else
        {
          color1=0;
          color2=255;
        }
        pixels.setPixelColor((i_quaet+2*9)+ind+8-count, pixels.Color(color1,color2,0));
        pixels.setPixelColor((i_quaet+6*9)+ind+8-count, pixels.Color(color1,color2,0));
        pixels.setPixelColor((i_quaet+5*9)+k_quaet, pixels.Color(color1,color2,0));
        pixels.setPixelColor((i_quaet+1*9)+k_quaet, pixels.Color(color1,color2,0));
        pixels.show();
        delay(50);
        count++;
      }
  
      
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////



/*

void rainbowCirclePix(uint16_t ind, uint16_t numb)
{

  switch(numb)
  {
    case 0: rainbowCircleZero(); break; 
    case 1: rainbowCircleOne(); break;
    case 2: rainbowCircleTwo(); break;
    case 3: rainbowCircleThree(); break;
    case 4: rainbowCircleFour(); break;
    case 5: rainbowCircleFive(); break;
    case 6: rainbowCircleSix(); break;
    case 7: rainbowCircleSeven(); break;
    case 8: rainbowCircleEight(); break;
    case 9: rainbowCircleNine(); break;
    default: return;
  }
  
  
}


void rainbowCircleZero()
{
  
}

void rainbowCircleOne()
{
  
}

void rainbowCircleTwo()
{
  
}

void rainbowCircleThree()
{
  
}

void rainbowCircleFour()
{
  
}

void rainbowCircleFive()
{

}

void rainbowCircleSix()
{
  
}

void rainbowCircleSeven()
{
  
}

void rainbowCircleEight()
{
  
}

void rainbowCircleNine()
{
  
}

void rainbowCircleClear(uint16_t ind)
{
  for(uint16_t i=0;i<9;i++)
    pixels.setPixelColor((i+4*9)+ind, pixels.Color(255,0,255));
  pixels.show();
  delay(1000);
  int count = 0;

  for(uint16_t k_k=0; k_k<18; k_k++)
  {
    if(ind-k_k<9)
      pixels.setPixelColor((k_k+5*9)+ind, pixels.Color(255,0,255));
    else 
      pixels.setPixelColor((k_k+6*9)+ind, pixels.Color(255,0,255));
    
    if((count%2))
      pixels.setPixelColor(i*9+ind, pixels.Color(255,0,255));
    pixels.show();
    delay(1000);         
  }
  
  for(uint16_t i=0;i<9;i++)
    pixels.setPixelColor((i+3*9)+ind, pixels.Color(255,0,255));
  
}
*/
