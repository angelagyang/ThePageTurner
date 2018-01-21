#include <Servo.h>
#include <Keyboard.h>
Servo servo;
const int trigPin = 12;
const int echoPin = 13;
const int dist = 5;
int pos = 0;

//we used the example sketches from Arduino's IDE to help write our code
void setup() {
  servo.attach(9); //motor's pin number
  pinMode(LED_BUILTIN, OUTPUT);
  Keyboard.begin();
  servo.write(180);
  Serial.begin(9600); 
}

void flipPage()
{
  //flips the page back down
  for (pos = 0; pos <= 180; pos += 1) { 
    servo.write(pos);
    delay(15);
  }
  //returns the flipper to its original position so it's ready to turn another page
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo.write(pos);
    delay(15);
  }
  //we used the LED on the Arduino Zero for debugging 
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                  
  digitalWrite(LED_BUILTIN, LOW);   
  delay(100);   
}

void loop() {
  long duration, cm;
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);

  //if the page is within distance of the ping sensor (i.e., it's been turned)
  if (cm < dist & cm != 0)
  {
    //moves one page down
    Keyboard.write(KEY_PAGE_DOWN);
    //delays 2 seconds before page gets flipped back
    delay(2000);
    //flip page back so it can be turned again    
    flipPage();
  }
}

/*calculates the distance from the ping sensor
 * by David A. Mellis and Tom Igoe (an example from
 * the Arduino Desktop IDE)*/
long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}


