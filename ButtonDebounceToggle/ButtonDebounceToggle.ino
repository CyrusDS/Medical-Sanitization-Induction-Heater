const int BigbuttonPin = 5;     // the number of the startingpushbutton pin
//int currentMillis = 0; //initial value for tracking time to compare to
//int currentMillisD = 0; //initial value for tracking time to compare to
//int currentMillisU = 0; //initial value for tracking time to compare to
long int delayTimeMS = 21500;  //starting heat time of 2 seconds
//const int ButtondownPin = 5;     // the number of the pushbutton pin for raising time
//const int ButtonupPin = 6;     // the number of the pushbutton pin for lowering time
const int ledPin =  3;      // the number of the LED pin
const int inductorSwitch =  2;      // the number of the inductor switch driver pin

// variables will change:
int buttonState = 0;         // variable for reading the starter pushbutton status
//int buttonUp = 0;// variable for reading the up time pushbutton status
//int buttonDown = 0;// variable for reading the down time pushbutton status
long int ldrStatus = 501;
long int failSafe = 0;
long int timeOn = 0;
long int totaltimeOn = 0;
long int offrecently = 2;
long int onrecently = 0;
long int debouncetime = 2000;
long int secondcounter = 0;
void setup() {
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pins as a pullup input to make it simple:
//  pinMode(ButtondownPin, INPUT_PULLUP);
  pinMode(BigbuttonPin, INPUT_PULLUP);
//  pinMode(ButtonupPin, INPUT_PULLUP);

  //4v control switch to inductor driver
  pinMode(inductorSwitch, OUTPUT);
}

void loop() {
  // read the state of the pushbutton values:
  buttonState = digitalRead(BigbuttonPin);
//  buttonUp = digitalRead(ButtonupPin);
//  buttonDown = digitalRead(ButtondownPin);
//  Serial.println(buttonState);
  if (buttonState == LOW) {
    //Serial.println("reset..");
    failSafe = 0;
    totaltimeOn = 0;
    onrecently = 0;
    offrecently = 0;
  }
//  Serial.println("On recently:");
//  Serial.println(onrecently);
//  Serial.println("Off recently:");
//  Serial.println(offrecently);
//  Serial.println("Time On:");
//  Serial.println(timeOn);
  //Serial.println("Currently:");
  totaltimeOn = totaltimeOn + 50;
  if (totaltimeOn >= 300000) {
    failSafe = 1;
    Serial.println("Turned off from total time");
  }
  if(onrecently >= 8 && offrecently >= 8) { //indicates lots of switching between states
    failSafe = 1;
    Serial.println("Turned off from strobing");
  }
  if(secondcounter >= debouncetime) {
    onrecently = 0;
    offrecently = 0;
    secondcounter = 0;
  }
  if (failSafe == 0) { //For input pullup, LOW means high. Same with above buttons for changing delay
      // turn LED on to indicate HEATING:
      onrecently = onrecently + 1;
      if (timeOn >= delayTimeMS) {
        timeOn = 0;
        failSafe = 1;
      }
      digitalWrite(ledPin, HIGH);
      digitalWrite(inductorSwitch, HIGH); //turn on heater
      //Serial.println(timeOn);
      timeOn = timeOn + 50;
        //Serial.println("on");
    }
  else {
    Serial.println("off...");
    offrecently = offrecently + 1;
    // turn LED off if you are no longer heating, or keep it off:
    digitalWrite(ledPin, LOW);
    digitalWrite(inductorSwitch, LOW);
    timeOn = 0;
  }
  secondcounter = secondcounter + 50;
  delay(50);
}