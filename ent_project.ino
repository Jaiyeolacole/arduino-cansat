#include <SoftwareSerial.h>

const int rxPin= 10;
const int txPin=11;
char incoming; // stores command from the bluetooth
int light1=6; 
int light2=3;
int fan=12;
int wallOutlet=7;
int state= LOW; // set the initial state of the device to off
int buzzer=2; // sounds each time a command is sent from the phone

//.....................................................................................................
SoftwareSerial bluetooth (rxPin, txPin);

void setup() {
  pinMode(8, HIGH);
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
   pinMode(light1, OUTPUT);
    pinMode(light2, OUTPUT);
     pinMode(fan, OUTPUT);
      pinMode(wallOutlet, OUTPUT);
      pinMode(buzzer, OUTPUT);
  if (bluetooth.isListening()) // if the bluetooth is working
  {
    Serial.println("bluetooth is listening");
  }
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void loop() {
  if (bluetooth.available())
  {
   incoming= bluetooth.read(); // read incoming command
  Serial.print("Received:");
  Serial.println(incoming);
  tone(buzzer,1000,500); // gives notifications
  }

  //------------------------------------------------------------------------------------------------------------------------
  //LIGHT 1 CONTROL
  if(incoming== '1') 
  {
    delay(50); // debouncing effect
    if(incoming== '1')
    {
       state = !state; // when command 1 is inputed, the state of the appliance should change. i.e low to high here
      digitalWrite(light1,state);
    } 
  }
  else if(incoming== '1' && state == HIGH) // if another signal come in while the appliance is high
    {
      state = !state; // change the state of the appliance again
     digitalWrite(light1,state);
    }

   //------------------------------------------------------------------------------------------------------------------------
  //LIGHT 2 CONTROL
  if(incoming== '2')
  {
    delay(50);
    if(incoming== '2')
    {
       state = !state;
      digitalWrite(light2, state);
    } 
  }
  else if(incoming== '2' && state == HIGH)
    {
      state = !state;
     digitalWrite(light2,state);
    }
   //------------------------------------------------------------------------------------------------------------------------
  //FAN CONTROL
 if(incoming== '3')
  {
    delay(50);
    if(incoming== '3')
    {
       state = !state;
      digitalWrite(fan, state);
    } 
  }
  else if(incoming== '3' && state == HIGH)
    {
      state = !state;
     digitalWrite(fan, state);
    }

   //------------------------------------------------------------------------------------------------------------------------
  //WALLOUTLET CONTROL
  if(incoming== '4')
  {
    delay(50);
    if(incoming== '4')
    {
       state = !state;
      digitalWrite(wallOutlet, state);
    } 
  }
  else if(incoming== '4' && state == HIGH)
    {
      state = !state;
     digitalWrite(wallOutlet, state);
    }
   //------------------------------------------------------------------------------------------------------------------------
  //ALL APPLIANCES CONTROL
  if(incoming== '0')
  {
    delay(50);
    if(incoming== '0')
    {
     state= !state;
     digitalWrite(light1, state);
     digitalWrite(light2, state);
     digitalWrite(fan, state);
     digitalWrite(wallOutlet, state);
    }
    else if (incoming== '0' && state == HIGH)
    {
      state= !state;
      digitalWrite(light1, state);
     digitalWrite(light2, state);
     digitalWrite(fan, state);
     digitalWrite(wallOutlet, state);
    }
    
  }
}
  


// code by REBORN
