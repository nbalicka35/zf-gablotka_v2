#define MOTION_SENSOR_PIN 2
#define ECHO_PIN 8
#define TRIGGER_PIN 7

void turn_led_on(){
    digitalWrite(LED_BUILTIN, HIGH);
}

void turn_led_off(){
    digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  pinMode(MOTION_SENSOR_PIN, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(9600);
}

void loop() {
  if(digitalRead(MOTION_SENSOR_PIN) == HIGH){
    turn_led_on();
  }
  else{
    turn_led_off();
  }
  delay(500);
}
