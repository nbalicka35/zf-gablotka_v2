// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)
#include <math.h>
#include "RTC.h"
#include <Adafruit_NeoPixel.h>
#include "DFRobot_VEML7700.h" /* sensor library */

//#include <winuser.h> wil be needed later
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    5
#define MOTION_SENSOR_PIN 2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 50
#define ECHO_PIN 8
#define TRIGGER_PIN 7
#define MAX_DISTANCE_CM 150
#define BRIGHTNESS_VALUE 60
#define buton_pin 4
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
DFRobot_VEML7700 als; /* instance of als object */

// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------
enum brightness_levels{
  very_dark = 12,
  dark = 25,
  light_dark = 50,
  very_light_bright = 100,
  light_bright = 200,
  medium_bright = 300,
  bright = 400,
  very_bright = 500,
  strong_bright = 600,
  max_brightness = 700
};
enum distance_e{
  closest = 10,
  closer = 20,
  close = 30,
  far = 40,
  further = 50,
  furthest = 60
};
enum button_states : byte{
    undefined = 0,
    prev = 1,
    next = 2,
    colorChange = 3
};
void distance_checker(int distance_in_cm){
    Serial.print("Distance (in cm): ");
    Serial.println(distance_in_cm);
    Serial.println();
if(distance_in_cm <= 10){
      for(int i=0; i<strip.numPixels() && i>50; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
          for(int i=0; i<50; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
    }
    else if(distance_in_cm > 10 && distance_in_cm <= 20){
      for(int i=0; i<strip.numPixels() && i>40; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
          for(int i=0; i<40; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
    }
    else if (distance_in_cm > 20 && (distance_in_cm <= 30)){
      for(int i=0; i<strip.numPixels() && i>30; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
          for(int i=0; i<30; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show(); 
    }
    else if (distance_in_cm > 30 && (distance_in_cm <= 40)){
      
          for(int i=20; i<strip.numPixels(); i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
          for(int i=0; i<20; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show(); 
    }
    else if (distance_in_cm > 40 && (distance_in_cm <= 50)){
      
          for(int i=10; i<strip.numPixels(); i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
          for(int i=0; i<10; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show(); 
    }
    else {
      for(int i=0; i<50; i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,0));  
          strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
          }strip.show(); 
    }

}
void breathe(uint32_t del,uint32_t color){

      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
         strip.setPixelColor(i, color);  
                 //  Set pixel's color (in RAM)                           //  Pause for a moment
       }
       strip.show();
      for(int i =1; i < (BRIGHTNESS_VALUE / 10) + 1;i++){
        strip.setBrightness(i*10);
        strip.show();
        delay(50);
      }
      
    delay(del);
    for(int i =(BRIGHTNESS_VALUE / 10); i > 0;i--){
        strip.setBrightness(i*10);
        strip.show();
        delay(50);
        
      }
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        strip.setPixelColor(i, color);  
                //  Set pixel's color (in RAM)                           //  Pause for a moment
      }
      strip.show();
}
void ligthing_intensity(float illuminance){
  float logB = 255 * (log10((illuminance+1))/2)/ log10(120000+1);
  int mappedB = constrain((int)logB,0,255);
  Serial.println(mappedB);
  strip.setBrightness(mappedB);
  strip.show();
  // if(illuminance < very_dark){
  //   strip.setBrightness(6);
  //   strip.show();
  // }
  // else if (illuminance < dark){
  //   strip.setBrightness(12);
  //   strip.show();
  //   }
  // else if (illuminance < light_dark){
  //   strip.setBrightness(25);
  //   strip.show();
  //   }
  // else if (illuminance < very_light_bright){
  //   strip.setBrightness(50);
  //   strip.show();
  //   }
  // else if (illuminance < light_bright){
  //   strip.setBrightness(75);
  //   strip.show();
  // }
  // else if (illuminance < medium_bright){
  //   strip.setBrightness(100);
  //   strip.show();
  // }
  // else if (illuminance < bright){
  //   strip.setBrightness(125);
  //   strip.show();
  // }
  // else if (illuminance < very_bright){
  //   strip.setBrightness(150);
  //   strip.show();
  // }
  // else if (illuminance < strong_bright){
  //   strip.setBrightness(175);
  //   strip.show();
  // }
  // else if (illuminance < max_brightness){
  //   strip.setBrightness(200);
  //   strip.show();
  // }
}
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  pinMode(MOTION_SENSOR_PIN, INPUT);
  //delay(60000); // wait 60 seconds on startup, so 
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIGGER_PIN, OUTPUT);
  als.begin();
  /* setup serial in purpose to print out measured distance */
  Serial.begin(9600);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(40);
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
          strip.setPixelColor(i, strip.Color(0,0,255));  
                 //  Set pixel's color (in RAM)                           //  Pause for a moment
          }
strip.show();  // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------


char check = 0;

void loop() {
  
  float illuminance, w_illuminance,a_illuminance, aw_illuminance;
  Serial.println(digitalRead(MOTION_SENSOR_PIN));
  if(digitalRead(MOTION_SENSOR_PIN) == HIGH){
  als.getALSLux(illuminance); /* Illuminance measured */
  Serial.print("Lux measured: ");
  Serial.println(illuminance);
  digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(5);
    /* transmit 4kHz wave for 10 us */
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    /* measure for how many microseconds echo pin is in high state (receives signal) */
    int duration = pulseIn(ECHO_PIN, HIGH);
    /* sound velocity = 340 m/s => 0.034 cm/us, divided by 2 because distance is doubled (signal transmitted and then received) */
    int distance_in_cm = duration * 0.034 / 2;

    
    
    //breathe(3000,strip.Color(0,255,0));
    
    ligthing_intensity(illuminance);
    //tutaj moze delay, ale do przedyskutowania
    //delay(10);
  }
    // else{
    //   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    //   strip.setPixelColor(i, strip.Color(0,0,255));  
    //   strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
    //   }
    // }
    
    // if (distance_in_cm <=MAX_DISTANCE_CM && check ==0){
    //   check = 1;
    //   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    //      strip.setPixelColor(i, strip.Color(0,0,255));  
    //              //  Set pixel's color (in RAM)                           //  Pause for a moment
    //    }
    //    //strip.setBrightness(1);
    //    strip.show();
    //   for(int i =1; i < 6;i++){
    //     strip.setBrightness(i*10);
    //     strip.show();
    //     delay(50);
    //   }
    //   // for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    //   //  strip.setPixelColor(i, strip.Color(0,0,255));  
    //   //  strip.show();        //  Set pixel's color (in RAM)                           //  Pause for a moment
    //   // }
    // }
    
    // else if(distance_in_cm >MAX_DISTANCE_CM && check ==1){
    //   check = 0;
    //   for(int i =5; i >=1;i--){
    //     strip.setBrightness(i*10);
    //     strip.show();
    //     delay(50);
        
    //   }
    //   for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    //     strip.setPixelColor(i, strip.Color(0,0,0));  
    //             //  Set pixel's color (in RAM)                           //  Pause for a moment
    //   }
    //   strip.show();
    // }
  //delay(1000);
  //strip.setBrightness(100);  
  // Fill along the length of the strip in various colors...
  // colorWipe(strip.Color(255,   0,   0), 50); // Red
  // colorWipe(strip.Color(  0, 255,   0), 50); // Green
  // // colorWipe(strip.Color(  0,   0, 255), 50); // Blue

  // // Do a theater marquee effect in various colors...
  // theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  // theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  // theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

  // rainbow(10);             // Flowing rainbow cycle along the whole strip
  // theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  
  /*als.getWhiteLux(w_illuminance);
  als.getAutoALSLux(a_illuminance);
  als.getAutoWhiteLux(aw_illuminance);
  Serial.print(" white illuminance lux measured: ");
  Serial.print(w_illuminance);
  Serial.print(" auto illuminance lux measured: ");
  Serial.print(a_illuminance);
  Serial.print(" auto white illuminance lux measured: ");
  Serial.println(aw_illuminance);*/
  
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this loop:
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    // strip.rainbow() can take a single argument (first pixel hue) or
    // optionally a few extras: number of rainbow repetitions (default 1),
    // saturation and value (brightness) (both 0-255, similar to the
    // ColorHSV() function, default 255), and a true/false flag for whether
    // to apply gamma correction to provide 'truer' colors (default true).
    strip.rainbow(firstPixelHue);
    // Above line is equivalent to:
    // strip.rainbow(firstPixelHue, 1, 255, 255, true);
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}