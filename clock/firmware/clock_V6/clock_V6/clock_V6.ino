
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>



#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      252

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int c = 1;
byte colorset[3] = {255,0,0}; 
byte colorsetrainbow[3] = {0,0,255};
uint16_t i, j, k, t;

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

byte time_now[4];
byte time_last[4] = {0,0,0,0};

int delayval = 500; // delay for half a second

void setup() {
  Serial.begin(9600);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.





  
}
byte sim = 0;

void loop() {

 
//
//   Start numbers: 1-st is 0 
//                  2-d is 63
//                  3-d is 126
//                  4-th is 189
//

     rainbow();
}


void rainbow()
{   
     uint16_t i, j;
     if(((time_now[0] >= 1) && (time_now[1] >= 7))|| (time_now[0]==2))
     { c=0;
 //pixels.show();
  for(j=0; j<252*5; j++) { 
    for(i=0; i< pixels.numPixels(); i++) {
      if(pixels.getPixelColor(i) == 0)
        pixels.setPixelColor(i, 0,0,0);
        else
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show(); 
    }
    
    }
    else
    {
      c=1;
      //delay(500);
    }
     readTime();
      
    //delay(500);
  
    
}

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



void readTime()
{
   tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
   // Serial.println(tm.Hour);
//    Serial.println((tm.Hour/10));
//    Serial.println((tm.Hour%10));
    Serial.print(tm.Hour);
    Serial.println(':');
//    Serial.println((tm.Minute/10));
//    Serial.println((tm.Minute%10));
    Serial.println(tm.Minute);

    time_now[0] =  tm.Hour/10;
    time_now[1] =  tm.Hour%10;
    time_now[2] =  tm.Minute/10;
    time_now[3] =  tm.Minute%10;
    Serial.print(time_now[0]);
    Serial.print(time_now[1]);
    Serial.print(time_now[2]);
    Serial.print(time_now[3]);
    
  }
  int count = 0;
  for (t=0; t<4; t++)
  {
    if (time_now[t] != time_last[t])
      {
      if(count==0)
        rainbowPix();
        count++; 
      numberPix();       
      time_last[t] = time_now[t];
     
      }

  }
}
////////////////////////////////////////////////////////////////////////////////////



//num - цифра; ind1 - номер табло; 
void numberPix()
{ uint16_t ind;
 
        
  
  for (int q=0;q<4;q++)
  {
    for (i=0; i<7; i++) {
      switch(q)
  {
    case 0: ind=0;break;
    case 1: ind=63;break;
    case 2: ind=126;break;
    case 3: ind=189;break;
    default: return;
  }
      if (digits[time_now[q]][i]) {
           
          for (k=ind; k<ind+9; k++)              
                pixels.setPixelColor(((i*9)+k), pixels.Color( colorset[0], colorset[1], colorset[2]));     
      }
      else
        {
          for (k=ind; k<ind+9; k++)
          {
            pixels.setPixelColor(((i*9)+k), pixels.Color(0,0,0));
          }     
     // if(c = 1)
        

    }
        
}
  }
  pixels.show();
  delay(100);
  
}
  

//explosion rainbow trigger
void rainbowPix()
{

  uint16_t color1;
  uint16_t color2;
  uint16_t count=0,count2 = 0;
  uint16_t i_quaet=0;
 
      for (uint16_t k_quaet=0;k_quaet<9;k_quaet++)
      {  
        pixels.setPixelColor((i_quaet*9)+k_quaet, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+3*9)+8-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+4*9)+k_quaet, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));

        delay(10);
      
       
        pixels.setPixelColor((i_quaet*9)+k_quaet+63, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+3*9)+71-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+4*9)+k_quaet+63, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
 
        delay(10);
                
        pixels.setPixelColor(((i_quaet)*9)+k_quaet+126, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+3*9)+134-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet+4)*9)+k_quaet+126, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));



        delay(10);

        pixels.setPixelColor(((i_quaet)*9)+k_quaet+189, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+3*9)+197-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+4*9)+k_quaet+189, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        
        pixels.show();
       
        count++;
      }
    
    count =0;
    i_quaet=0;
      for (uint16_t k_quaet=0;k_quaet<9;k_quaet++)
     {
        pixels.setPixelColor((i_quaet+2*9)+8-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+6*9)+8-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+5*9)+k_quaet, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor((i_quaet+1*9)+k_quaet, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
       
        delay(10);

        pixels.setPixelColor(((i_quaet)+2*9)+71-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+6*9)+71-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+5*9)+(k_quaet+63), pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+1*9)+(k_quaet+63), pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
 
        delay(10);

        pixels.setPixelColor(((i_quaet)+2*9)+134-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+6*9)+134-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+5*9)+k_quaet+126, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+1*9)+k_quaet+126, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));

        delay(10);

        pixels.setPixelColor(((i_quaet)+2*9)+197-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+6*9)+197-count, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+5*9)+k_quaet+189, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
        pixels.setPixelColor(((i_quaet)+1*9)+k_quaet+189, pixels.Color(colorsetrainbow[0],colorsetrainbow[1],colorsetrainbow[2]));
                
        pixels.show();
       
        count++; 
      }
 }



