#include "SIM900.h" 
#include <SoftwareSerial.h> 
#include "sms.h" 
#include "DHT.h" 
#include <Wire.h> 
#include <LiquidCrystal.h> 
#include <Adafruit_LiquidCrystal.h> 
Adafruit_LiquidCrystal lcd(12, 11,6, 5, 4, 3); 
SMSGSM sms; 
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 
int numdata; 
boolean started=false; 
char smsbuffer[160]; 
char n[20]; 
char sms_position; 
char phone_number[20];
char sms_text[100]; 
int i; 
float t; 
float h; 
void setup() 
{ 
Serial.begin(9600); 
lcd.begin(16, 2); 
lcd.print("Sensing Humidity"); 
lcd.setCursor(0, 1); 
lcd.print("and temperture"); 
delay(2000); 
dht.begin(); 
if (gsm.begin(9600)) 
{ 
Serial.println("\nstatus=READY"); 
started=true; 
} 
else 
Serial.println("\nstatus=IDLE"); 
Serial.println("DHT11 Output!"); 
}; 
void loop() 
{ 
h = dht.readHumidity(); 
t = dht.readTemperature(); 
Serial.print("Humidity: "); 
Serial.print(h); 
lcd.begin(16, 2); 
lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0 
lcd.print("Humidity: "); // Prints Sensor Val: to LCD 
lcd.print(h); 
lcd.print(" %\t");
delay(5000); 
Serial.print("Temperature: "); 
Serial.print(t); 
lcd.setCursor(0,0); // Sets the cursor to col 0 and row 0 
lcd.print("Temperature: "); // Prints Sensor Val: to LCD 
lcd.setCursor(0,1); 
lcd.print(t); 
lcd.print(" C\t"); 
delay(5000); 
if(isnan(t) || isnan(h)){ 
Serial.println("Failed to read DHT11"); 
}else{ 
if(t <= 20) 
{ 
if (sms.SendSMS("Phonenumber", "The Temperature is between 15 and 20,Press button LOW ")) 
{ 
Serial.println("\nSMS sent OK."); 
} 
else 
{ 
Serial.println("\nError sending SMS."); 
} 
} 
else if(t>=21 && t <= 24) 
{ 
if (sms.SendSMS("Phonenumber", "The Temperature is between 20 and 25,Press button Medium")) 
{ 
Serial.println("\nSMS sent OK."); 
} 
else 
{ 
Serial.println("\nError sending SMS."); 
} 
}
else 
{ 
if (sms.SendSMS("Phonenumber", "The Temperature is above 25,Press button HIGH ")) 
{ 
Serial.println("\nSMS sent OK."); 
} 
else 
{ 
Serial.println("\nError sending SMS."); 
} 
} 
} 
};

