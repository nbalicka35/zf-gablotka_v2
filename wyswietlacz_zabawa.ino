#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

static const char hello_msg[] = "Hello World";
static const char msg1[] = "Podswietlenie"; 
static const char msg2[] = "Gablotka ZF!";

void setup() {
  lcd.begin(16, 2); 
  lcd.setCursor(0, 0);
  lcd.print(F(hello_msg));
  lcd.setCursor(0, 1);
  lcd.print(F(msg2));
}

void update_second_line(const char* text) {
  lcd.setCursor(0, 1);
  lcd.print(F("                "));
  lcd.setCursor(0, 1);
  lcd.print(F(text));
}

void loop() {
  update_second_line(msg1);
  delay(2000);
  update_second_line(msg2);
  delay(2000);
}