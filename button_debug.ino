#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int oldValue = LOW,
oldValue1 = LOW,
oldValue2 = LOW,
oldValue3 = LOW ; 
char table[100] = "Button 8:  \nButton 9:  \nButton 10:  \nButton 11:  \0";
void setup() 
{
  Serial.begin(115200);
  Serial.println("Press the button.");
  
  // Initialize the pin for reading the button.
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
}

void loop() 
{
  int newValue = digitalRead(8),
  newValue1 = digitalRead(9),
  newValue2 = digitalRead(10),
  newValue3 = digitalRead(11);
  table[10] = newValue + '0';
  table[22] = newValue1 + '0';
  table[35] = newValue2 + '0';
  table[48] = newValue3 + '0';
  if(newValue != oldValue || newValue1 != oldValue1 || newValue2 != oldValue2 || newValue3 != oldValue3)
  {
    Serial.println(table);
    oldValue = newValue;
    oldValue1 = newValue1;
    oldValue2 = newValue2;
    oldValue3 = newValue3;
  }

  delay(100);
}