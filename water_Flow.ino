#include <LiquidCrystal_I2C.h>

const int flowSensorPin = 2;  
volatile int flowPulseCount = 0;  
unsigned long lastPulseTime = 0;  
float flowRate = 0.0;  
const float pulsesPerLiter = 450.0;  
float x;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  pinMode(flowSensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);

  Serial.begin(9600);
  Serial.println("Water Flow Sensor Test");
  lcd.init();
  lcd.backlight();
}


void loop() {
  unsigned long currentMillis = millis();
  if ((currentMillis - lastPulseTime) >= 1000) {

    flowRate = (flowPulseCount / pulsesPerLiter) * 60.0;
    x=flowRate/10;

    Serial.print("Flow Rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");
    lcd.setCursor(0,0);
    lcd.print(flowRate, 1);
    lcd.print("Lts in ");
    lcd.print(flowRate,0);
    lcd.print("Min");
    lcd.setCursor(0,1);
    lcd.print(x, 2);
    lcd.print("L/min");

    flowPulseCount = 0;  
    lastPulseTime = currentMillis;  
  }
}

void pulseCounter() {
  flowPulseCount++;
}
