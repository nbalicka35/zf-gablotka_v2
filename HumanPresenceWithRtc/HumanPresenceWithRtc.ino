#include <ThreeWire.h>
#include <RtcDS1302.h>

// Pin definitions for clear hardware mapping
#define RTC_CLK_PIN 5
#define RTC_DAT_PIN 4  
#define RTC_RST_PIN 3
#define MMWAVE_GPIO_PIN 6

// Business hours configuration
#define WORK_START_HOUR 6    // 6:00 AM
#define WORK_END_HOUR 16     // 4:00 PM (16:00 in 24h format)

// Day of week constants (DS1302 format: Sunday=0, Monday=1, ..., Saturday=6)
#define SUNDAY 0
#define MONDAY 1
#define TUESDAY 2
#define WEDNESDAY 3
#define THURSDAY 4
#define FRIDAY 5
#define SATURDAY 6

// Initialize RTC communication
ThreeWire myWire(RTC_DAT_PIN, RTC_CLK_PIN, RTC_RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

// Global variables for system state tracking
bool lastPresenceState = false;
unsigned long lastDebugTime = 0;
const unsigned long DEBUG_INTERVAL = 10000; // Debug output every 10 seconds

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  Serial.println("=== Arduino Uno R4 WiFi Presence Detection System ===");
  Serial.println("Initializing components...");
  
  // Configure built-in LED for presence indication
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Built-in LED initialized");
  
  // Configure mmWave sensor GPIO pin as input
  pinMode(MMWAVE_GPIO_PIN, INPUT);
  Serial.println("mmWave sensor GPIO configured");
  
  // Initialize RTC module
  initializeRTC();
  
  Serial.println("System initialization complete");
  Serial.println("Monitoring for presence during business hours...");
  Serial.println();
}

void loop() {
  // Get current date and time from RTC
  RtcDateTime currentTime = Rtc.GetDateTime();
  
  // Validate RTC data integrity
  if (!currentTime.IsValid()) {
    Serial.println("ERROR: RTC data invalid - check battery and connections");
    delay(5000);
    return;
  }
  
  // Check if current time falls within business hours
  bool inBusinessHours = isBusinessHours(currentTime);
  
  // Only process presence detection during business hours
  if (inBusinessHours) {
    bool currentPresence = isPresenceDetected();
    
    // Detect presence state changes for efficient processing
    if (currentPresence != lastPresenceState) {
      if (currentPresence) {
        Serial.print("PRESENCE DETECTED at ");
        printFormattedTime(currentTime);
        handlePresenceDetected();
      } else {
        Serial.print("Presence cleared at ");
        printFormattedTime(currentTime);
        digitalWrite(LED_BUILTIN, LOW);
      }
      lastPresenceState = currentPresence;
    }
    
    // Flash LED continuously while presence is detected
    if (currentPresence) {
      flashPresenceLED();
    }
  } else {
    // Ensure LED is off outside business hours
    digitalWrite(LED_BUILTIN, LOW);
    
    // Reset presence state when outside business hours
    if (lastPresenceState) {
      lastPresenceState = false;
      Serial.println("Presence monitoring paused - outside business hours");
    }
  }
  
  // Periodic debug output for system monitoring
  periodicDebugOutput(currentTime, inBusinessHours);
  
  // Small delay to prevent excessive polling while maintaining responsiveness
  delay(100);
}

void initializeRTC() {
  Serial.println("Initializing DS1302 RTC module...");
  
  Rtc.Begin();
  
  // Set initial time if RTC has lost power or is invalid
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  
  if (!Rtc.IsDateTimeValid()) {
    Serial.println("RTC lost confidence - setting to compile time");
    Rtc.SetDateTime(compiled);
  }
  
  if (Rtc.GetIsWriteProtected()) {
    Serial.println("RTC write protected - enabling writes");
    Rtc.SetIsWriteProtected(false);
  }
  
  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC not running - starting clock");
    Rtc.SetIsRunning(true);
  }
  
  // Display current RTC time for verification
  RtcDateTime now = Rtc.GetDateTime();
  Serial.print("RTC initialized - Current time: ");
  printFormattedTime(now);
  Serial.println();
}

bool isBusinessHours(RtcDateTime dateTime) {
  int dayOfWeek = dateTime.DayOfWeek();
  int hour = dateTime.Hour();
  
  // Check if current day is Monday through Friday
  bool isBusinessDay = (dayOfWeek >= MONDAY && dayOfWeek <= FRIDAY);
  
  // Check if current hour is within 6 AM to 4 PM range
  bool isWorkingHour = (hour >= WORK_START_HOUR && hour < WORK_END_HOUR);
  
  return isBusinessDay && isWorkingHour;
}

bool isPresenceDetected() {
  // Read GPIO2 pin from mmWave sensor
  // HIGH indicates presence detected, LOW indicates no presence
  return digitalRead(MMWAVE_GPIO_PIN) == HIGH;
}

void handlePresenceDetected() {
  // Current implementation: LED flashing for proof of concept
  // In final version, replace this section with actual functionality:
  // - Bluetooth notifications
  // - Data logging
  // - External device control
  // - Network communications
  
  Serial.println("Executing presence response actions...");
  
  // Placeholder for future functionality
  // executeBluetoothNotification();
  // logPresenceEvent();
  // controlExternalDevices();
}

void flashPresenceLED() {
  // Simple LED flashing pattern for presence indication
  static unsigned long lastFlashTime = 0;
  static bool ledState = false;
  
  unsigned long currentMillis = millis();
  
  // Flash every 500ms for clear visual indication
  if (currentMillis - lastFlashTime >= 500) {
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
    lastFlashTime = currentMillis;
  }
}

void periodicDebugOutput(RtcDateTime currentTime, bool inBusinessHours) {
  unsigned long currentMillis = millis();
  
  if (currentMillis - lastDebugTime >= DEBUG_INTERVAL) {
    Serial.println("--- System Status ---");
    Serial.print("Current time: ");
    printFormattedTime(currentTime);
    Serial.print("Day of week: ");
    Serial.println(getDayName(currentTime.DayOfWeek()));
    Serial.print("Business hours: ");
    Serial.println(inBusinessHours ? "YES" : "NO");
    Serial.print("Presence detected: ");
    Serial.println(lastPresenceState ? "YES" : "NO");
    Serial.print("LED state: ");
    Serial.println(digitalRead(LED_BUILTIN) ? "ON" : "OFF");
    Serial.println("--------------------");
    Serial.println();
    
    lastDebugTime = currentMillis;
  }
}

void printFormattedTime(RtcDateTime dateTime) {
  // Format: YYYY-MM-DD HH:MM:SS
  Serial.print(dateTime.Year());
  Serial.print("-");
  if (dateTime.Month() < 10) Serial.print("0");
  Serial.print(dateTime.Month());
  Serial.print("-");
  if (dateTime.Day() < 10) Serial.print("0");
  Serial.print(dateTime.Day());
  Serial.print(" ");
  if (dateTime.Hour() < 10) Serial.print("0");
  Serial.print(dateTime.Hour());
  Serial.print(":");
  if (dateTime.Minute() < 10) Serial.print("0");
  Serial.print(dateTime.Minute());
  Serial.print(":");
  if (dateTime.Second() < 10) Serial.print("0");
  Serial.print(dateTime.Second());
}

String getDayName(int dayOfWeek) {
  switch(dayOfWeek) {
    case SUNDAY: return "Sunday";
    case MONDAY: return "Monday";
    case TUESDAY: return "Tuesday";
    case WEDNESDAY: return "Wednesday";
    case THURSDAY: return "Thursday";
    case FRIDAY: return "Friday";
    case SATURDAY: return "Saturday";
    default: return "Unknown";
  }
}
