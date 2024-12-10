// C++ code
//
#include <Servo.h>

Servo lockservo;
Servo openservo;

const int onPin = 13;
const int offPin = 8;
const int openLED = 3;
const int closeLED = 2;
const int piezoPin = 6;
const int ldrPin = A0;


bool doorIsOpen = false; // Track the door state

void lock(){
  	delay(2000);
	lockservo.write(0);
}
void unlock(){
	lockservo.write(90);
  	delay(2000);
}
void openDoor(){
  if (!doorIsOpen) { // Only send a message if the door state has changed
    
    tone(piezoPin, 2000); 
    
    digitalWrite(openLED, HIGH);//green
    digitalWrite(closeLED, LOW);
    
    unlock();
    openservo.write(180);
    
    Serial.println("Door is OPEN!");
    doorIsOpen = true; // Update door state
    
    delay(5000);
    noTone(piezoPin);
    
  }
}

void closeDoor(){
  if (doorIsOpen) {// Only send a message if the door state has changed
   

    int lightValue = analogRead(ldrPin); // Read the light value
    Serial.print("Light value:");
    Serial.println(lightValue);

    if(lightValue>225){
      openservo.write(0);
      lock();
      digitalWrite(closeLED, HIGH);//red
      digitalWrite(openLED, LOW);
      
      Serial.println("Door is CLOSED!");
      doorIsOpen = false; // Update door state
    }else{
      Serial.println("Interrupting the door");
      closeDoor();
    }
  }
 
}
void setup()
{
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(openLED,OUTPUT);
  pinMode(closeLED,OUTPUT);
  pinMode(onPin,INPUT);
  pinMode(offPin,INPUT);
  pinMode(piezoPin, OUTPUT);
  
  lockservo.attach(4);  // Attach lockservo to pin 4
  openservo.attach(5); // Attach openservo to pin 5
  
  lockservo.write(0);
  openservo.write(0);
  digitalWrite(closeLED, HIGH);//red
  digitalWrite(openLED, LOW);
  Serial.println("Door is CLOSED!");
  
  
}

void loop()
{
  
  if(digitalRead(onPin)==HIGH){
    openDoor();
    
  }else if(digitalRead(offPin)==HIGH){
    closeDoor();
  }
}