#include <SoftwareSerial.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>

#define DHTPIN 2     
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

SoftwareSerial BlueToothPin(10,11); //rx and tx pin

//****************************************************************************************************************************************
//variable declarations
int potpin = 1; //potentiomenter pin or pressure sensor input
int servoPin = 9; //servo pin
int val, height;
float humidity, temperature;
bool potExceed50 = false;
int beacon = 4; // audio beacon pin
int BeaconValue;

Servo servo;
//*****************************************************************************************************************************************
bool state = false;

void setup() {
  pinMode(beacon, LOW);
  Serial.begin(9600);
  servo.attach(servoPin);
  dht.begin();
  BlueToothPin.begin(9600);
}

void loop() { 
  delay(20);
  
  TempHumid();
  turnServo();
  audioBeacon();
  BT();
  
//  Serial.println(" \t HEIGHT \t HUMIDITY \t TEMPERATURE \t PARACHUTE_STATE \t BEACON");
  if(BlueToothPin.available()){
    Serial.print("BLUETOOTH: \t");
    Serial.println("Connected");
  }
  else{
    Serial.print("BLUETOOTH: \t");
    Serial.println("Not Connected");
  }
    Serial.print("HEIGHT: \t");
    Serial.print(height);
    Serial.println("cm");

    Serial.print("HUMIDITY: \t");
    Serial.print(humidity);
    Serial.println("%");

    Serial.print("TEMPRATURE: \t");
    Serial.print(temperature);
    Serial.println("*C");

    Serial.print("PARACHUTE: \t");
  if(state == false){
    Serial.println("CLOSED \t ");
  }
  else{
    Serial.println("OPENED \t ");
  }
    
   if( BeaconValue < 5 and state == true){
     digitalWrite(beacon, HIGH);
     Serial.print("BEACON: \t");
     Serial.println("ON \n");
  }
  else{
    Serial.print("BEACON: \t");
    Serial.println("OFF \n"); 
  }
}
//******************************************************************************************************************************************
//this is for unlocking servo that houses the parachute
void turnServo(){
  
   int pressure = analogRead(potpin);
   height = map(pressure, 0, 1023, 0, 1000);
   servo.write(5);

   if( height > 750){
    potExceed50 = true;
    state = false;
   }
   
   if (potExceed50 == true and height < 750){
    servo.write(101);
    state = true;
   }
}

//***************************************************************************************************************************************************
//function for getting enviromental temperature and humidity

void TempHumid() {
  delay(2000);

  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    return;
  }
}

//****************************************************************************************************************************************************
//Audio beacon indicator
int audioBeacon(){
    int *BeaconHeight = &height;
    BeaconValue = *BeaconHeight;
    return BeaconValue;
}

// **************************************************************************************************************************************************
//Bluetooth communication function
void BT(){
  if(BlueToothPin.available()){
    char c = BlueToothPin.read();
    Serial.println(c);
  }
}
