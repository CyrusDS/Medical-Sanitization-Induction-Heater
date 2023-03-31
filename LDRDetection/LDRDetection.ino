const int BigbuttonPin = 4;     // the number of the startingpushbutton pin
int currentMillis = 0; //initial value for tracking time to compare to
int currentMillisD = 0; //initial value for tracking time to compare to
int currentMillisU = 0; //initial value for tracking time to compare to
long int delayTimeMS = 90000;  //starting heat time of 2 seconds
unsigned long debounceDelay = 250;    // the debounce time; increase if the output flickers

const int ButtondownPin = 5;     // the number of the pushbutton pin for raising time
const int ButtonupPin = 6;     // the number of the pushbutton pin for lowering time
const int ldrPin = A5;
const int ledPin =  3;      // the number of the LED pin
const int inductorSwitch =  2;      // the number of the inductor switch driver pin

// variables will change:
int buttonState = 0;         // variable for reading the starter pushbutton status
int buttonUp = 0;// variable for reading the up time pushbutton status
int buttonDown = 0;// variable for reading the down time pushbutton status
int ldrStatus = 501;
int failSafe = 0;
int timeOn = 0;
void setup() {
  //Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pins as a pullup input to make it simple:
  pinMode(ButtondownPin, INPUT_PULLUP);
  pinMode(BigbuttonPin, INPUT_PULLUP);
  pinMode(ButtonupPin, INPUT_PULLUP);
  pinMode(ldrPin, INPUT);

  //4v control switch to inductor driver
  pinMode(inductorSwitch, OUTPUT);
}

void loop() {
  // read the state of the pushbutton values:
  ldrStatus = analogRead(ldrPin);
  buttonState = digitalRead(BigbuttonPin);
  buttonUp = digitalRead(ButtonupPin);
  buttonDown = digitalRead(ButtondownPin);
  Serial.println(ldrStatus);
  if (buttonState == LOW) {
    failSafe = 0;
  }

  if (ldrStatus <= 320 && failSafe == 0) { //For input pullup, LOW means high. Same with above buttons for changing delay
      // turn LED on to indicate HEATING:
      if (timeOn >= 30000) {
        timeOn = 0;
        failSafe = 1;
      }
      digitalWrite(ledPin, HIGH);
      digitalWrite(inductorSwitch, HIGH); //turn on heater
      //Serial.println(timeOn);
      timeOn = timeOn + 100;
      delay(100);
    }
  else {
    // turn LED off if you are no longer heating, or keep it off:
    digitalWrite(ledPin, LOW);
    digitalWrite(inductorSwitch, LOW);
    timeOn = 0;
  }
}
