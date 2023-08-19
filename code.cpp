// power up
// Button press Feed interval selection
// Feed interval LED light on for selected interval
// Other Feed Interval LEDs switch off
// timer starts for feed interval
// Button press Feed duration selection
// Feed duration LED light on for selected interval
// Other Feed duration LEDs switch off
// Override feed button - manual dispensing of food

// constants won't change.  They're used here to set the pin numbers:
const int twentyfourLedPin = 13;
const int twelveLedPin = 12;
const int sixLedPin = 11;
const int twentyfourbuttonPin = A0;
const int twelvebuttonPin = A1;
const int sixbuttonPin = A2;
const int longLedPin = 7;
const int medLedPin = 6;
const int shortLedPin = 5;
const int longbuttonPin = A3;
const int medbuttonPin = A4;
const int shortbuttonPin = A5;
const int feedPin = 4;
const int feedLedPin = 2;
const int manualbuttonPin = 3;


//variables will change:  variables for reading the pushbutton status. 
//initialise the state of the buttons to "not pressed"
int twentyfourbuttonState = 0;
int twelvebuttonState = 0;
int sixbuttonState = 0;
int longbuttonState = 0;
int medbuttonState = 0;
int shortbuttonState = 0;
int manualbuttonState = 0;
int feedduration;//time in seconds that the feed will dispense food for
int feedinterval = 1000; //time in hours that the feeder will activate

unsigned long myTime;
unsigned long elapsedTime;
unsigned long seconds;
unsigned long minutes;
unsigned long hours;

void setup() {
  // put your setup code here, to run once:
  //assign pinouts to Feed Interval and Feed duration LEDs
  //assign pinouts to selection buttons (3 Feedints, 1 manualoverride)
  pinMode(twentyfourLedPin, OUTPUT); //24hr LED
  pinMode(twentyfourbuttonPin, INPUT_PULLUP); //24hr Button
  pinMode(twelveLedPin, OUTPUT); //12hr LED
  pinMode(twelvebuttonPin, INPUT_PULLUP); //12hr Button
  pinMode(sixLedPin, OUTPUT); //6hr LED
  pinMode(sixbuttonPin, INPUT_PULLUP); //6hr button
  pinMode(longLedPin, OUTPUT); //Long feed LED
  pinMode(longbuttonPin, INPUT_PULLUP);//Long feed Button
  pinMode(medLedPin, OUTPUT); //Med feed LED
  pinMode(medbuttonPin, INPUT_PULLUP); //Med feed Button
  pinMode(shortLedPin,OUTPUT); //Short feed LED
  pinMode(shortbuttonPin,INPUT_PULLUP); //Short feed Button
  pinMode(manualbuttonPin,INPUT_PULLUP); // Manual feed Button
  pinMode(feedPin, OUTPUT); //Feed motor relay
  pinMode(feedLedPin, OUTPUT);//feed LED
Serial.begin(9600); //this turns arduino's monitor on so I can check stuff
}

void loop() {
//main code here, to run repeatedly:

//read the state of the pushbutton values:
twentyfourbuttonState = digitalRead(twentyfourbuttonPin);
twelvebuttonState = digitalRead(twelvebuttonPin); 
sixbuttonState = digitalRead(sixbuttonPin);
longbuttonState = digitalRead(longbuttonPin);
medbuttonState = digitalRead(medbuttonPin);
shortbuttonState = digitalRead(shortbuttonPin);
manualbuttonState = digitalRead(manualbuttonPin);

//FEED INTERVAL  SELECTION
if (twentyfourbuttonState == LOW) {
  // turn 24hr LED on:
  digitalWrite(twentyfourLedPin, HIGH);
  digitalWrite(twelveLedPin, LOW);
  digitalWrite(sixLedPin, LOW);
  feedinterval=24;
  myTime = millis();
} 
if (twelvebuttonState == LOW) {
  digitalWrite(twentyfourLedPin, LOW);
  // turn 12hr LED on:
  digitalWrite(twelveLedPin, HIGH);
  digitalWrite(sixLedPin, LOW);
  feedinterval=12;
  myTime = millis();
}
 if (sixbuttonState == LOW){
   // turn 6hr LED on:
   digitalWrite(twentyfourLedPin, LOW);
   digitalWrite(twelveLedPin, LOW);
   digitalWrite(sixLedPin, HIGH);
   feedinterval=6;
   myTime = millis();
}
//FEED DURATION SELECTION
if (longbuttonState == LOW) {
  // turn long feed duration LED on:
  digitalWrite(longLedPin, HIGH);
  digitalWrite(medLedPin, LOW);
  digitalWrite(shortLedPin, LOW);
  feedduration=10;
}
if (medbuttonState == LOW) {
  // turn long feed duration LED on:
  digitalWrite(longLedPin, LOW);
  digitalWrite(medLedPin, HIGH);
  digitalWrite(shortLedPin, LOW);
  feedduration=7;
} 
if (shortbuttonState == LOW) {
  digitalWrite(longLedPin, LOW);
  digitalWrite(medLedPin, LOW);
  // turn short feed duration LED on:
  digitalWrite(shortLedPin, HIGH);
  feedduration=5;
}
  
//MANUAL FEED  
if (manualbuttonState==LOW){
   digitalWrite(feedPin, HIGH);
  digitalWrite(feedLedPin, HIGH);
}
if (manualbuttonState==HIGH){
  digitalWrite(feedPin, LOW);
  digitalWrite(feedLedPin, LOW);
}

//the timer...
 elapsedTime = millis()-myTime;
 seconds = elapsedTime/1000;
 minutes = seconds/60;
 hours = minutes/60;

// activating the dispenser   
  if (hours >= feedinterval) {
  digitalWrite(feedPin, HIGH);
  digitalWrite(feedLedPin, HIGH);
  delay(feedduration*1000);
  digitalWrite(feedPin, LOW);
  digitalWrite(feedLedPin, LOW);
  myTime = millis();
 }

//Serial.print("ElapsedTime: ");
//Serial.println(elapsedTime);
//Serial.print("Hours: ");
//Serial.print(hours);
//Serial.print("  Minutes: ");
//Serial.print(minutes);
Serial.print("  Seconds: ");
Serial.println(seconds);
Serial.print("Feed :");
Serial.print(feedinterval);

}
