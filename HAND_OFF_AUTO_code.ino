#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 3

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int handDial = A0;
const int motorPin = 9;
const int buttonPin = 2;
const int handLED = 4;
const int autoLED = 5;
const int ESDLED = 6;
const int ESDbutton = 7;
const int resetButton = 10;

bool motorState = false;
bool handMode = false;
bool autoMode = false;
bool ESDMode = false;

int lastButtonState = LOW;
int lastESDButtonState = LOW;
int lastResetButtonState = LOW;

int motorSpeed = 0;
float temperatureC = 0;
int estimatedRPM = 0;
unsigned long lastTempRead = 0;

int lastMode = -1;

unsigned long lastBlink = 0;
bool esdVisible = true;


void setup() {
  Serial.begin(9600);

  pinMode(handDial, INPUT);
  //pinMode(DHTPIN, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ESDbutton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
	
  pinMode(motorPin, OUTPUT);
  pinMode(handLED, OUTPUT);
  pinMode(autoLED, OUTPUT);
  pinMode(ESDLED, OUTPUT);
  
  lcd.init();
  lcd.backlight();

  dht.begin();
  delay(2000);
}

void loop() {

  int buttonState = digitalRead(buttonPin);
  int ESDbuttonState = digitalRead(ESDbutton);
  int resetButtonState = digitalRead(resetButton);
	
  if (ESDbuttonState == LOW && lastESDButtonState == HIGH){
    handMode = false;
    autoMode = false;
    ESDMode = true;
    //ACTIVATE ESD MODE IF ESD BUTTON PRESSED
  }else{
    if (buttonState == LOW && lastButtonState == HIGH){
      delay(50);
      motorState = !motorState;
    }
    lastButtonState = buttonState;
    //PROCEED WITH HAND-AUTO CONTROL IF ESD BUTTON NOT PRESSED
  }
  lastESDButtonState = ESDbuttonState;
  
  
  if (resetButtonState == LOW && lastResetButtonState == HIGH){
    ESDMode = !ESDMode;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("RESETTED");
    delay(1000);
    lcd.clear();
    //DEACTIVATE ESD MODE IF RESET BUTTON PUSHED
  }
  lastResetButtonState = resetButtonState;
  
  if (!ESDMode){
    //IF THERE IS NO EMERGENCY SHUTDOWN
    if (motorState){
      //HAND MODE
      handMode = true;
      autoMode = false;
      ESDMode = false;
      
      digitalWrite(handLED, HIGH);
      digitalWrite(autoLED, LOW);
      digitalWrite(ESDLED, LOW);
      
    } else {
      // AUTO MODE
      handMode = false;
      autoMode = true;
      ESDMode = false;
      
      digitalWrite(handLED, LOW);
      digitalWrite(autoLED, HIGH);
      digitalWrite(ESDLED, LOW);
    
    }
  
  }
  
  int currentMode;
  if (ESDMode) currentMode = 2;
  else if (handMode) currentMode = 0;
  else currentMode = 1;
  
  if (handMode == true && autoMode == false && ESDMode == false){
    //CONTROLS SPEED BASED ON 
    int dialValue = analogRead(handDial);

    int minPWM = 40;
    if (dialValue < 130){
      motorSpeed = 0;
    }else {
      motorSpeed = map(dialValue, 130, 1023, minPWM, 255);
    }
    
    motorSpeed = constrain(motorSpeed, 0, 255);
    analogWrite(motorPin, motorSpeed);
    
    //DISPLAYS TEMPERATURE AT ALL TIMES
    if (millis() - lastTempRead >= 1000){
      lastTempRead = millis();

      float t = dht.readTemperature();

      Serial.print("Temperature: ");
      Serial.print(t);

      if (!isnan(t)){
        temperatureC = t;
        
      }else {
        Serial.println("Failed to read!!!");
      }
    }

    //DISPLAY ON LCD
    estimatedRPM = map(motorSpeed, 0, 255, 0, 17482);
    
    if (currentMode != lastMode) {
      lcd.clear();
      lastMode = currentMode;
    }
    
    char buffer[16];
    sprintf(buffer, "RPM:%5d", estimatedRPM);
    lcd.setCursor(0,0);
    lcd.print(buffer);
    
    lcd.setCursor(11,0);
    lcd.print("HAND");
    
    lcd.setCursor(0,1);
    lcd.print("TMP:");
    lcd.print(temperatureC);
    lcd.print("C");
  
  }else if (handMode == false && autoMode == true && ESDMode == false){
    //CONTROLS SPEED BASED ON TEMPERATURE


    if (millis() - lastTempRead >= 1000){
      lastTempRead = millis();

      float t = dht.readTemperature();

      Serial.print("Temperature: ");
      Serial.println(t);

      if (!isnan(t)){
        temperatureC = t;
      }else {
        Serial.println("Failed to read!!!");
      }
    }

	  motorSpeed = map((int)temperatureC, -40, 50, 0, 255);
	  motorSpeed = constrain(motorSpeed, 0, 255);
    
    analogWrite(motorPin, motorSpeed);
    
    //DISPLAY ON LCD 
    estimatedRPM = map(motorSpeed, 0, 255, 0, 17482);
    
    if (currentMode != lastMode) {
      lcd.clear();
      lastMode = currentMode;
    }
    
    
    char buffer[16];
    sprintf(buffer, "RPM:%5d", estimatedRPM);
    lcd.setCursor(0,0);
    lcd.print(buffer);
    
    lcd.setCursor(11,0);
    lcd.print("AUTO");
    
    lcd.setCursor(0,1);
    lcd.print("TMP:");
    lcd.print(temperatureC);
    lcd.print("C");
  
  }else if (handMode == false && autoMode == false && ESDMode == true){
    //COMPLETELY SHUTS DOWN MOTOR
    digitalWrite(handLED, LOW);
    digitalWrite(autoLED, LOW);
    digitalWrite(ESDLED, HIGH);
    analogWrite(motorPin, 0);
    
    //DISPLAY ON LCD
    if (millis() - lastBlink >= 250){
      lastBlink = millis();
      esdVisible = !esdVisible;
    }
   
    if (esdVisible){
      lcd.setCursor(0,0);
      lcd.print("!!!EMERGENCY!!!");
      
      lcd.setCursor(0,1);
      lcd.print("    SHUTDOWN    ");
    
    } else {
      lcd.clear();
    
    }
         

  }
}
