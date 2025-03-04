#include <stdio.h>
#include <DS1302.h>
#include <Wire.h>
#include <math.h>
#include <Adafruit_NeoPixel.h>  /* library for the LED strip control https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest/strandtest.ino */
#include "DFRobot_VEML7700.h" /* ambient light sensor library */

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif


#define LED_COUNT 50 /* @define Amount of addressable pixels on the LED strip, max is 50, but if you wish to change the limit below this threshold, you can do it here */
#define MAX_DISTANCE_CM 150 /* @define max distance which will be acceptable by our system, subject to changes in the future */
#define BRIGHTNESS_VALUE 60 /* @define limits the light intensity in breathe function, subject to change*/




#define ECHO_PIN 8 /* @pin where to plug ultrasonic sensor, specifically ECHO pin, which listens for the incoming wave*/
#define TRIGGER_PIN 7 /* @pin where to plug ultrasonic sensor, specifically TRIGGER pin, which emits the wave*/
#define LED_PIN    6 /* @pin where to plug LED strip */
#define MOTION_SENSOR_PIN 2 /* @pin where to plug motion sensor */

namespace {
  // DS1302 RTC pins
  const int kCePin   = 5;  // Chip Enable
  const int kIoPin   = 7;  // Input/Output (changed from 6 to avoid conflict with LED_PIN)
  const int kSclkPin = 8;  // Serial Clock (changed from 7 to avoid conflicts)
  
  // Create a DS1302 object
  DS1302 rtc(kCePin, kIoPin, kSclkPin);
  
  // Create NeoPixel object
  Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
  
  // Variables for RTC refresh timing
  unsigned long lastRtcRefreshTime = 0;
  const unsigned long rtcRefreshInterval = 30 * 60 * 1000; // 30 minutes in milliseconds
  // Initialize with a placeholder value, will be updated in setup
  Time rtcTimeCache(2025, 1, 1, 0, 0, 0, Time::kWednesday);
  
  String dayAsString(const Time::Day day) {
    switch (day) {
      case Time::kSunday: return "Sunday";
      case Time::kMonday: return "Monday";
      case Time::kTuesday: return "Tuesday";
      case Time::kWednesday: return "Wednesday";
      case Time::kThursday: return "Thursday";
      case Time::kFriday: return "Friday";
      case Time::kSaturday: return "Saturday";
    }
    return "(unknown day)";
  }

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // Declare our NeoPixel strip object
DFRobot_VEML7700 als; /* instance of als object */

/* @enum these serve purpose of setting brightness levels, left for later use */
enum brightnessLevels_e{
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
/* @enum these serve purpose of distance declaration, should be used within distance_checker function */
enum distance_e{
  closest = 10,
  closer = 20,
  close = 30,
  far = 40,
  further = 50,
  furthest = 60
};
/* @enum these serve purpose of defining button states, which are not yet implemented due to time constraint, subject to change*/

enum button_states : byte{
    undefined = 0,
    prev = 1,
    next = 2,
    colorChange = 3
};

/*
@brief Chekcs for the distance by calculating how long it took for a generated sound wave to come back to the sensor
For further references seek information in the docs: https://www.micros.com.pl/mediaserver/M_HY-SRF05_0003.pdf
*/
void distance_checker(){
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
  Serial.print("Distance (in cm): ");
  Serial.println(distance_in_cm);
  Serial.println();
  /* checks for the amount of pixels needed to be activated in relation to the distance bracket. Further the reigstered object, less pixels will be activated. Arbitrary distance ranges made for easier debugging, needs adjustments before releasing for production.*/
  if(distance_in_cm <= 10){
    //first loops are always responsible for "clearing" colors by setting it to black. I HIGHY DISCOURAGE from setting brightness to 0, since strip would always require activation and it might be impractical.
    for(int i=0; i<strip.numPixels() && i>50; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    }
    for(int i=0; i<50; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,255));  
      strip.show();        
    }       
  }
  else if(distance_in_cm > 10 && distance_in_cm <= 20){
    for(int i=0; i<strip.numPixels() && i>40; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    }
    for(int i=0; i<40; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,255));  
      strip.show();        
    }
                
  }
  else if (distance_in_cm > 20 && (distance_in_cm <= 30)){
    for(int i=0; i<strip.numPixels() && i>30; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    }
    for(int i=0; i<30; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,255));  
      strip.show();        
    } 
  }
  else if (distance_in_cm > 30 && (distance_in_cm <= 40)){
    for(int i=20; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    }
    for(int i=0; i<20; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,255));  
      strip.show();        
    }
  }
  else if (distance_in_cm > 40 && (distance_in_cm <= 50)){
    for(int i=10; i<strip.numPixels(); i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    }
    for(int i=0; i<10; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,255));  
      strip.show();        
    }
  }
  else {
    for(int i=0; i<50; i++) { 
      strip.setPixelColor(i, strip.Color(0,0,0));  
      strip.show();        
    } 
  }

}

/* @brief Emulates a breathing effect. 
   
  @param del - delay (in miliseconds) passed to the delay function, type unsigned integer
  @param color - 32 bit definition of color created by strip.Color() function, don't input your own values if you don't know what you are doing
*/
void breathe(uint32_t del,uint32_t color){
  /* This loop is responsible for setting defined color */
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);  
  }
  /* DON'T REMOVE THESE SINCE THEY ARE REQUIRED TO APPLY CHANGES MADE TO LED STRIP */
  strip.show();
  /* First "wave" of the breathing effect */
  for(int i =1; i < (BRIGHTNESS_VALUE / 10) + 1;i++){
    strip.setBrightness(i*10);
    strip.show();
    delay(50);
  }
  /* This delay is required to emulate breathing effect. DON'T REMOVE */
  delay(del);
  
  /* Second "wave" of the breathing effect */
  for(int i = (BRIGHTNESS_VALUE / 10); i > 0;i--){
    strip.setBrightness(i*10);
    strip.show();
    delay(50);
  }
  for(int i=0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);  
  }
  strip.show();
}

/* 
  @brief Function used for adjusting lighting intensity when LED is set to static color display mode. First iteration relied on adjusting lighting based on the sensor's measurmenet and statically checking ranges from enum.
  Now we simply plug the measurement into log function and calculate it's respective value.
  @Param illuminance - measurement registered from light sensor

*/
void ligthing_intensity(float illuminance){
  float logB = 255 * (log10((illuminance+1))/2)/ log10(120000+1);
  int mappedB = constrain((int)logB,0,255);
  Serial.println(mappedB);
  strip.setBrightness(mappedB);
  strip.show();
  /* DON'T REMOVE, IT'S NOT ARCHIVED */
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
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pinMode(MOTION_SENSOR_PIN, INPUT);

  //delay(60000); // wait 60 seconds on startup, comment for debugging, uncomment for production
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
                 //  Set pixel's color (in RAM)                           
          }
strip.show(); 
}


// loop() function -- runs repeatedly as long as board is on ---------------


char check = 0;

void loop() {
  
  float illuminance, w_illuminance,a_illuminance, aw_illuminance;
  Serial.println(digitalRead(MOTION_SENSOR_PIN));
  /* ALL BUSINESS LOGIC HAS TO BE INSERTED INTO THIS IF STATEMENT, since we anticipate the start of the flow from PIR activation. */
  if(digitalRead(MOTION_SENSOR_PIN) == HIGH){
    als.getALSLux(illuminance); /* Illuminance measured */
    Serial.print("Lux measured: ");
    Serial.println(illuminance);
    distance_checker();
    ligthing_intensity(illuminance);
    /* For now this mode is optional, requires further integration with buttons */
    //breathe(3000,strip.Color(0,255,0));
    
    
    //tutaj moze delay, ale do przedyskutowania
    //delay(10);
  }  
}






